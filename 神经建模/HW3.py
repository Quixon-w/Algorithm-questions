import numpy as np
from sklearn.preprocessing import LabelEncoder
from sklearn.naive_bayes import CategoricalNB

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

encoders = [LabelEncoder() for _ in range(len(features[0]))]
features_encoded = np.array([encoders[i].fit_transform([row[i] for row in features]) for i in range(len(features[0]))]).T

target_encoder = LabelEncoder()
target_encoded = target_encoder.fit_transform(target)

model = CategoricalNB()
model.fit(features_encoded, target_encoded)

input_data = ["高", "多云", "中", "明亮"]
input_encoded = [encoders[i].transform([input_data[i]])[0] for i in range(len(input_data))]
input_encoded = np.array(input_encoded).reshape(1, -1)

prediction_encoded = model.predict(input_encoded)
prediction = target_encoder.inverse_transform(prediction_encoded)[0]
print("预测结果是："+prediction)
