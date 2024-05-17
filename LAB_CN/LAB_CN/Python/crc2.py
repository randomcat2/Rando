def xor(a, b):
	result = []
	for i in range(1, len(b)):
		if a[i] == b[i]:
			result.append('0')
		else:
			result.append('1')
	return ''.join(result)

def division(data, divisor):
	pick = len(divisor)
	temp = data[:pick]
	while pick < len(data):
		if temp[0] == '1':
			temp = xor(divisor,temp) + data[pick]
		else:
			temp = xor('0'*pick, temp) + data[pick]

		pick += 1

	if temp[0] == '1':
			temp = xor(divisor,temp) 
	else:
			temp = xor('0'*pick, temp) 

	return temp

def encode_crc(data, divisor):
	append_data = data + '0' * (len(divisor)-1)
	print("Number of 0's to be appended: ",(len(divisor)-1))
	print("Message after appending 0's: ",append_data)
	remainder = division(append_data, divisor)
	codewode = data + remainder
	print("Remainder: ",remainder)
	print("Encoded data: ",codewode)
	return codewode

def decode_crc(data, divisor):
	decoded_data = division(data, divisor)
	print("Remainder: ",decoded_data)
	if decoded_data == '0' * len(decoded_data):
		return True
	else:
		return False

def main():
	f = input("Enter frame: ")
	
	g = input("Enter generator: ")

	print("Sender side:")
	print("Frame: ",f)
	print("Generator: ",g)

	encoded_data = encode_crc(f,g)

	print("Receiver side: ")
	print("Received frame: ",encoded_data)

	d = decode_crc(encoded_data,g)
	if(d):
		print("\nSince Remainder Is 0 Hence Message Transmitted From Server To Client Is Correct")
	else:
		print("\nSince Remainder Is Not 0 Hence Message Transmitted From Server To Client Contains Error")

if __name__ == '__main__':
	main()