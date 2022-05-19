'''
Регистр сдвига с линейной обратной связью

Состояние q - битовая последовательность длины 4
Автомат не использует входные данные.

Функция выхода lfsr_output возвращает последний справа бит.

Функция перехода lfsr_transition сдвигает биты влево на 1 и
приписывает справа бит, вычисленный с помощью линейной функции
обратной связи linear_feedback

'''

# XOR 0, 2 и 3 битов и единицы (нумерация битов справа налево)
def linear_feedback( q ):
    q0 = int( q[ 3 ] )
    q2 = int( q[ 1 ] )
    q3 = int( q[ 0 ] )
    return str( q0 ^ q2 ^ q3 ^ 1 )


def lfsr_transition( x_unused, q ):
    return q[ 1: ] + linear_feedback( q )


def lfsr_output( x_unused, q ):
    return q[ 0 ]
