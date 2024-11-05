import numpy as np
from collections import defaultdict
from math import log

data = [
    ["高", "多云", "小", "明亮", "是"],
    ["正常", "多云", "中", "阴暗", "是"],
    ["高", "少云", "小", "明亮", "否"],
    ["正常", "少云", "小", "明亮", "否"],
    ["正常", "多云", "中", "明亮", "否"],
    ["高", "多云", "中", "阴暗", "是"],
    ["高", "少云", "大", "阴暗", "是"],
    ["正常", "多云", "小", "阴暗", "否"],
    ["正常", "少云", "中", "明亮", "否"],
    ["正常", "多云", "大", "明亮", "是"],
    ["正常", "少云", "小", "阴暗", "是"],
    ["正常", "少云", "大", "明亮", "否"],
]

features = [row[:-1] for row in data]
target = [row[-1] for row in data]

feature_names = ["天气", "云量", "风力", "光照"]
target_classes = list(set(target))

unique_values = [list(set([row[i] for row in features])) for i in range(len(features[0]))]
feature_indices = {name: i for i, name in enumerate(feature_names)}

feature_encoded = np.array([[unique_values[i].index(row[i]) for i in range(len(row))] for row in features])

#计算先验概率
class_counts = defaultdict(int)
for cls in target:
    class_counts[cls] += 1

total_samples = len(target)
class_probabilities = {cls: class_counts[cls] / total_samples for cls in target_classes}

#计算条件概率
conditional_probs = defaultdict(lambda: defaultdict(lambda: defaultdict(int)))

for i, row in enumerate(features):
    class_label = target[i]
    for j, feature_value in enumerate(row):
        feature_name = feature_names[j]
        value_index = unique_values[j].index(feature_value)
        conditional_probs[class_label][feature_name][value_index] += 1


for class_label in conditional_probs:
    for feature_name in conditional_probs[class_label]:
        total_class_count = class_counts[class_label]
        for value_index in conditional_probs[class_label][feature_name]:
            conditional_probs[class_label][feature_name][value_index] /= total_class_count

#预测
def predict(input_data):
    input_encoded = [unique_values[i].index(input_data[i]) for i in range(len(input_data))]
    posterior_probs = {}
    for class_label in target_classes:
        log_prob = log(class_probabilities[class_label])
        for j, feature_value in enumerate(input_data):
            feature_name = feature_names[j]
            value_index = unique_values[j].index(feature_value)
            log_prob += log(conditional_probs[class_label][feature_name].get(value_index, 1e-10))
        posterior_probs[class_label] = log_prob

    return max(posterior_probs, key=posterior_probs.get)

# 测试数据
input_data = ["高", "多云", "中", "明亮"]
prediction = predict(input_data)
print(f"预测结果：{prediction}")
