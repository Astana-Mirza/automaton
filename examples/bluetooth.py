'''
Комбайнер генератора Bluetooth

Вход x и состояние q - битовые последовательности длины 4
Выход y - один бит

Функция перехода - bt_transition
Функция возврата результата - bt_output

'''

def bt_transition( x, q ):
    assert len( x ) == 4, "input must have length 4"
    assert all( c in '01' for c in x ), "input must consist of 0s and 1s"
    q = list( map( int, q ) )
    s = ( x.count( '1' ) + q[ 2 ] + 2 * q[ 3 ] ) // 2
    s = [ s // 2, s % 2 ]
    return str( q[ 2 ] ) + str( q[ 3 ] )            +    \
           str( s[ 0 ] ^ q[ 0 ] ^ q[ 1 ] ^ q[ 2 ] ) +    \
           str( s[ 1 ] ^ q[ 0 ] ^ q[ 3 ] )


def bt_output( x, q ):
    assert len( x ) == 4, "input must have length 4"
    assert all( c in '01' for c in x ), "input must consist of 0s and 1s"
    q2 = int( q[ 2 ] )
    return str( ( x.count( '1' ) + q2 ) % 2 )
