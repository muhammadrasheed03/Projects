import matplotlib.pyplot as plt

# Function to read coordinates from a file
def read_coordinates(file_path):
    coordinates = []
    with open(file_path, 'r') as file:
        for line in file:
            x, y = map(float, line.strip().split())
            coordinates.append((x, y))
    return coordinates

# Function to plot the delivery route with directional arrows
def plot_path_with_arrows(coordinates):
    plt.figure(figsize=(8, 6))

    # Plot edges
    for i in range(len(coordinates) - 1):
        x_start, y_start = coordinates[i]
        x_end, y_end = coordinates[i + 1]
        plt.quiver(
            x_start, y_start,
            x_end - x_start, y_end - y_start,
            angles='xy', scale_units='xy', scale=1, color='red', width=0.01
        )
    # last node to the first for a closed loop
    x_start, y_start = coordinates[-1]
    x_end, y_end = coordinates[0]
    plt.quiver(
        x_start, y_start,
        x_end - x_start, y_end - y_start,
        angles='xy', scale_units='xy', scale=1, color='red', width=0.01, linestyle='dotted'
    )



    # Plot nodes
    for i, (x, y) in enumerate(coordinates):
        plt.scatter(x, y, color='cyan', s=300, zorder=2)
        plt.text(x, y, f"{i}", fontsize=20, color="black")

    # Additional stuff
    plt.title("Multi-Truck System")
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.axis('equal')
    plt.show()

# coordinates from the file
file_path = "coords.txt"
coordinates = read_coordinates(file_path)
plot_path_with_arrows(coordinates)
