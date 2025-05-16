#!/usr/bin/python3

import matplotlib.pyplot as plt
import csv

# Path to your CSV file
csv_file = "../dubins_path.csv"

x_vals = []
y_vals = []

# Read the CSV file
with open(csv_file, "r") as file:
    reader = csv.reader(file)
    for row in reader:
        if len(row) >= 2:
            x_vals.append(float(row[0]))
            y_vals.append(float(row[1]))

# Plotting
plt.figure(figsize=(8, 6))
plt.plot(x_vals, y_vals, marker=".", linestyle="-")
plt.title("Dubins Path: X vs Y")
plt.xlabel("X")
plt.ylabel("Y")
plt.grid(True)
plt.axis("equal")  # Optional: equal scaling on both axes
plt.show()
