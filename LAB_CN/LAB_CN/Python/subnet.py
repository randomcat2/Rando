def main():
    ip = input("Enter IP Address: ")
    classip = determine_class(ip)
    print("Class:", classip)
    subnets = int(input("Enter the number of subnets: "))
    subnet_mask(ip, subnets)

def determine_class(ip):
    first_octet = int(ip.split(".")[0])
    if 1 <= first_octet <= 126:
        return 'A'
    elif 128 <= first_octet <= 191:
        return 'B'
    elif 192 <= first_octet <= 223:
        return 'C'
    elif 224 <= first_octet <= 239:
        return 'D'
    else:
        return 'E'

def subnet_mask(ip, subnets):
    octets = list(map(int, ip.split(".")))
    
    subnet_size = 256 // subnets
    print("Subnet Ranges:")
    for i in range(subnets):
        start = i * subnet_size
        end = (i + 1) * subnet_size - 1
        print("Subnet %d: %d.%d.%d.%d - %d.%d.%d.%d" % (
            i + 1, octets[0], octets[1], octets[2], start, octets[0], octets[1], octets[2], end
        ))

if __name__ == "__main__":
    main()
