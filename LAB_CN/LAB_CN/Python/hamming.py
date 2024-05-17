def calculate_parity_bits(data):
    p1 = data[0] ^ data[1] ^ data[3]
    p2 = data[0] ^ data[2] ^ data[3]
    p3 = data[1] ^ data[2] ^ data[3]
    return p1, p2, p3


def add_parity_bits(data):
    p1, p2, p3 = calculate_parity_bits(data)
    data.insert(0, p1)
    data.insert(1, p2)
    data.insert(3, p3)


def detect_and_correct_error(received_data):
    error_position = 0
    p1 = received_data[0] ^ received_data[2] ^ received_data[4] ^ received_data[6]
    p2 = received_data[1] ^ received_data[2] ^ received_data[5] ^ received_data[6]
    p3 = received_data[3] ^ received_data[4] ^ received_data[5] ^ received_data[6]
    error_position = p3 * 4 + p2 * 2 + p1
    if error_position != 0:
        print("Error on the position:", error_position)
        received_data[error_position - 1] = 1 - received_data[error_position - 1]
        print("Correct message is:", ''.join(map(str, received_data)))
    else:
        print("Congratulations! There is no error.")
        print("Received data:", ''.join(map(str, received_data)))


# Main code
data = input("Enter 4 bits of data one by one (separated by spaces): ").split()
data = [int(bit) for bit in data]
add_parity_bits(data)
print("Encoded data is:", ''.join(map(str, data)))
received_data = input("Enter received data bits one by one (separated by spaces): ").split()
received_data = [int(bit) for bit in received_data]
detect_and_correct_error(received_data)
