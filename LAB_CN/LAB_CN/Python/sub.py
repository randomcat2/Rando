def main():
    ip = input("Enter IP address: ")
    classip = determine_ip(ip)
    print("Class: ",classip)
    
    subnet = int(input("Enter nuber of subnets: "))
    subnet_mask(ip,subnet)
    
def determine_ip(ip):
    first_octate = int(ip.split('.')[0])
    if 1<= first_octate<=126:
        return 'A'
    elif 128<=first_octate<191:
        return 'B'
    elif 192 <= first_octate <= 223:
        return 'C'
    elif 224 <= first_octate <= 239:
        return 'D'
    elif 240<= first_octate<=255:
        return 'E'
    else: return 'Unknown'
    
def subnet_mask(ip,subnet):
    octate = list(map(int,ip.split(".")))
    
    subnnet_size = 256//subnet
    for i in range(subnet):
        start = i*subnnet_size
        end = (i+1) * subnnet_size -1
        print("Subnet %d: %d.%d.%d.%d - %d.%d.%d.%d" % (i+1,octate[0],octate[1],octate[2],start,octate[0],octate[1],octate[2], end))
 
if __name__ == '__main__':
    main()