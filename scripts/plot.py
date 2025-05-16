#!/usr/bin/python3

import matplotlib.pyplot as plt
import csv

# Path to your CSV file
csv_file = "../dubins_path.csv"

x_vals = []
y_vals = []
z_vals = []

# Read the CSV file
with open(csv_file, "r") as file:
    reader = csv.reader(file)
    for row in reader:
        if len(row) >= 3:
            x_vals.append(float(row[0]))
            y_vals.append(float(row[1]))
            z_vals.append(float(row[2]))

# Plotting
fig, axs = plt.subplots(2, 1, figsize=(8, 10))

# X vs Y subplot
axs[0].plot(x_vals, y_vals, marker=".", linestyle="-")
axs[0].set_title("Dubins Path: X vs Y")
axs[0].set_xlabel("X")
axs[0].set_ylabel("Y")
axs[0].grid(True)
axs[0].axis("equal")

# Z subplot
axs[1].plot(z_vals, marker=".", linestyle="-", color="green")
axs[1].set_title("Z vs Index")
axs[1].set_xlabel("Index")
axs[1].set_ylabel("Z")
axs[1].grid(True)

plt.tight_layout()
plt.show()
