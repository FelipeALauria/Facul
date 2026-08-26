def convert10to2(decimal_value):
    binary_result = ""
    parts = decimal_value.replace(",", ".")
    parts = parts.split(".")  

    if len(parts) > 2:  
        return "Número Inválido"

    for char in decimal_value:
        if char not in "0123456789.,":  
            return "Número Inválido"

    integer_part = int(parts[0])
    while integer_part > 0:  
        binary_result = str(integer_part % 2) + binary_result
        integer_part //= 2

    if len(parts) == 1:  
        return int(binary_result)

    binary_result += "."
    fraction_multiplier = 1
    decimal_part = float(decimal_value) - int(parts[0])  

    for _ in range(0, 10):  
        fraction_multiplier /= 2
        if decimal_part >= fraction_multiplier:
            decimal_part -= fraction_multiplier
            binary_result += "1"
        else:
            binary_result += "0"

    return float(binary_result)

decimal_input = input("Digite o número em base decimal:")

binary_output = convert10to2(decimal_input)

print(binary_output)