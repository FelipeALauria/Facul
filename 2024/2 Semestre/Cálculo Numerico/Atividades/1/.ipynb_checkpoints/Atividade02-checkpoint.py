def convert2to10(binary_value):
    decimal_result = 0
    fraction_multiplier = 1
    after_decimal_point = False

    for char in binary_value:
        if char in "-,": 
            return "Formatação numérica inválida."
        if char not in "01.":  
            return "Número inserido não é binário."

        if after_decimal_point: 
            fraction_multiplier /= 2

        if char == ".":
            after_decimal_point = True
        elif not after_decimal_point:  
            decimal_result = decimal_result * 2 + int(char)
        else:  
            decimal_result += fraction_multiplier * int(char)

    return float(decimal_result)


binary_input = input("Digite o número em base binária:")

decimal_output = convert2to10(binary_input)

print(decimal_output)