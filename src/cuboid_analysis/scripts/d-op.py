# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.stats import multivariate_normal

# `output.csv` の読み込み関数
def read_output_csv(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
    
    # 平均値の取得
    mean_height = float(lines[0].split(',')[1].strip())
    mean_width = float(lines[1].split(',')[1].strip())
    mean_depth = float(lines[2].split(',')[1].strip())

    # 分散共分散行列の取得
    cov_matrix = []
    for line in lines[4:]:
        cov_matrix.append([float(value) for value in line.split(',')])
    
    cov_matrix = np.array(cov_matrix)
    
    return np.array([mean_height, mean_width, mean_depth]), cov_matrix

# 平均と分散共分散行列の計算関数
def calculate_mean_and_covariance(data):
    # データが多次元配列の場合の処理
    mean = np.mean(data, axis=0)
    covariance = np.cov(data, rowvar=False)
    return mean, covariance

# 辺の期待値と分散共分散行列の定義
mean, covariance_matrix = read_output_csv('output.csv')

# 分散共分散行列を標準化する関数
def standardize_covariance_matrix(cov_matrix):
    std_dev = np.sqrt(np.diag(cov_matrix))
    return cov_matrix / np.outer(std_dev, std_dev)

# 標準化された分散共分散行列
standardized_cov_matrix = standardize_covariance_matrix(covariance_matrix)

# 多変量正規分布の尤度関数
def multivariate_normal_likelihood(data, mean, cov_matrix):
    mvn = multivariate_normal(mean=mean, cov=cov_matrix)
    return mvn.pdf(data)

# フィッシャー情報量行列の計算
def fisher_information_matrix(mean, cov_matrix):
    gradient = np.eye(len(mean))
    fisher_info_matrix = np.zeros_like(cov_matrix)

    for i in range(len(mean)):
        for j in range(len(mean)):
            gradient_ij = np.dot(gradient[i, :], np.dot(np.linalg.inv(cov_matrix), gradient[j, :].T))
            fisher_info_matrix[i, j] = gradient_ij

    return fisher_info_matrix

# D-optimalityの計算
def d_optimality(mean, cov_matrix):
    fisher_info_matrix = fisher_information_matrix(mean, cov_matrix)
    return np.linalg.det(fisher_info_matrix) ** (1/len(mean)), fisher_info_matrix

# 楕円の方程式を計算する関数
def calculate_ellipse(mean, cov_matrix):
    # 分散共分散行列を標準化する
    std_deviations = np.sqrt(np.diag(cov_matrix))
    normalized_covariance = cov_matrix / np.outer(std_deviations, std_deviations)

    # 分散共分散行列から固有値と固有ベクトルを計算する
    eigenvalues, eigenvectors = np.linalg.eig(normalized_covariance)

    # 固有値と固有ベクトルから楕円の半径を計算する
    radii = np.sqrt(eigenvalues)

    # 固有ベクトルを回転行列として使用して楕円の方程式を作成する
    orientation = eigenvectors.T
    theta = np.linspace(0, 2 * np.pi, 100)
    phi = np.linspace(0, np.pi, 100)
    x = radii[0] * np.outer(np.cos(theta), np.sin(phi))
    y = radii[1] * np.outer(np.sin(theta), np.sin(phi))
    z = radii[2] * np.outer(np.ones_like(theta), np.cos(phi))

    for i in range(len(x)):
        for j in range(len(x)):
            [x[i, j], y[i, j], z[i, j]] = np.dot([x[i, j], y[i, j], z[i, j]], orientation) + mean

    return x, y, z

# サンプルデータに基づいて D-optimality を計算
d_optimal_value, fisher_info = d_optimality(mean, standardized_cov_matrix)

# フィッシャー情報量の表示
print("Fisher Information Matrix:")
print(fisher_info)

# 分散共分散行列の3D散布図の描画
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# 分散共分散行列の対角成分の平方根が各変数の標準偏差
std_dev = np.sqrt(np.diag(standardized_cov_matrix))

# グリッドを作成
x = np.linspace(mean[0] - 3 * std_dev[0], mean[0] + 3 * std_dev[0], 100)
y = np.linspace(mean[1] - 3 * std_dev[1], mean[1] + 3 * std_dev[1], 100)
x, y = np.meshgrid(x, y)

# 多変量正規分布の確率密度関数を計算
z = multivariate_normal.pdf(np.dstack((x, y)), mean=mean[:2], cov=standardized_cov_matrix[:2, :2])

# 3D散布図の描画
ax.plot_surface(x, y, z, cmap='viridis', alpha=0.7)
ax.set_xlabel('Height')
ax.set_ylabel('Width')
ax.set_zlabel('Probability Density')
ax.set_title('Multivariate Normal Distribution')

# 誤差楕円体の描画
x_ellipse, y_ellipse, z_ellipse = calculate_ellipse(mean=mean, cov_matrix=standardized_cov_matrix)
ax.plot_surface(x_ellipse, y_ellipse, z_ellipse, color='b', alpha=0.3)

plt.show()

print("D-optimality:", d_optimal_value)
