"""
Комбайнер генератора ключевого потока VEST

Линейный автомат M1:
	Вход data_	- битовая строка длины 16
	Вход state_	- битовая строка длины 10
	Выход 		- битовая строка длины 10

	Функция перехода - vest_linear_transition
	Функция возврата результата - vest_linear_output

Нелинейный автомат M2:
	Вход data_	- битовая строка длины 10
	Вход state_ - битовая строка длины w (в данной реализации w = 83)
	Выход		- битовая строка длины m (в данной реализации m = 4)

	Функция перехода - vest_non_linear_transition
	Функция возврата результата - vest_non_linear_output

"""

def vest_linear_transition( data_, state_, key_ = "" ):
	assert len( data_ ) == 16 , "M1 input must have length 16"
	assert len( state_ ) == 10, "M1 state must have length 10"
	assert all( c in '01' for c in data_  ), "M1 input must consist of 0s and 1s"
	assert all( c in '01' for c in state_ ), "M1 state must consist of 0s and 1s"

	state_components = list( map( int, state_ ) )
	data_components  = list( map( int, data_ ) )
	transitions = [
		lambda data, state: state[ 1 ] ^ data[ 1 ] ^ data[ 4 ]  ^ data[ 5 ]  ^ data[ 11 ] ^ data[ 13 ] ^ 1,
		lambda data, state: state[ 2 ] ^ data[ 0 ] ^ data[ 2 ]  ^ data[ 6 ]  ^ data[ 8 ]  ^ data[ 14 ],
		lambda data, state: state[ 3 ] ^ data[ 3 ] ^ data[ 4 ]  ^ data[ 7 ]  ^ data[ 10 ] ^ data[ 15 ],
		lambda data, state: state[ 4 ] ^ data[ 0 ] ^ data[ 3 ]  ^ data[ 5 ]  ^ data[ 9 ]  ^ data[ 12 ],
		lambda data, state: state[ 5 ] ^ data[ 1 ] ^ data[ 4 ]  ^ data[ 6 ]  ^ data[ 12 ] ^ data[ 15 ] ^ 1,
		lambda data, state: state[ 6 ] ^ data[ 0 ] ^ data[ 7 ]  ^ data[ 9 ]  ^ data[ 13 ] ^ data[ 14 ],
		lambda data, state: state[ 7 ] ^ data[ 1 ] ^ data[ 8 ]  ^ data[ 11 ] ^ data[ 14 ] ^ data[ 15 ],
		lambda data, state: state[ 8 ] ^ data[ 2 ] ^ data[ 5 ]  ^ data[ 6 ]  ^ data[ 10 ] ^ data[ 12 ] ^ 1,
		lambda data, state: state[ 0 ] ^ data[ 0 ] ^ data[ 3 ]  ^ data[ 7 ]  ^ data[ 8 ]  ^ data[ 9 ]  ^ 1,
		lambda data, state: state[ 9 ] ^ data[ 8 ] ^ data[ 10 ] ^ data[ 12 ] ^ data[ 13 ] ^ data[ 15 ] ^ 1
	]
	new_state = ""
	for i in range( 10 ):
		new_state += str( transitions[ i ]( data_components, state_components ) )

	return new_state


def vest_linear_output( data_, state_, key_ = "" ):
	assert len( data_ ) == 16 , "M1 input must have length 16"
	assert len( state_ ) == 10, "M1 state must have length 10"
	assert all( c in '01' for c in data_  ), "M1 input must consist of 0s and 1s"
	assert all( c in '01' for c in state_ ), "M1 state must consist of 0s and 1s"

	return state_


def vest_non_linear_transition( data_, state_, key_ = "" ):
	assert len( data_ ) == 10 , "M2 input must have length 10"
	assert len( state_ ) == 83, "M2 state must have length 83"
	assert all( c in '01' for c in data_  ), "M2 input must consist of 0s and 1s"
	assert all( c in '01' for c in state_ ), "M2 state must consist of 0s and 1s"

	data_components  = list( map( int, data_ ) )
	state_components = list( map( int, state_ ) )
	output_combiner = {
		0  : [0 , 1 , 2 , 3 , 4 , 58],
		1  : [0 , 1 , 2 , 3 , 4 , 47],
		2  : [0 , 1 , 2 , 3 , 4 , 36],
		3  : [0 , 1 , 2 , 3 , 4 , 27],
		4  : [0 , 1 , 2 , 3 , 4 , 11],
		5  : [4 , 4 , 1 , 3 , 2 , 20],
		6  : [5 , 5 , 2 , 4 , 3 , 78],
		7  : [6 , 6 , 3 , 0 , 4 , 70],
		8  : [7 , 7 , 0 , 1 , 5 , 77],
		9  : [8 , 8 , 5 , 2 , 6 , 56],
		10 : [9 , 9 , 6 , 8 , 7 , 35],
		11 : [9 , 9 , 8 , 10, 0 , 62],
		12 : [11, 11, 8 , 5 , 6 , 64],
		13 : [11, 11, 12, 6 , 10, 44],
		14 : [13, 10, 7 , 5 , 9 , 26],
		15 : [9 , 11, 8 , 13, 12, 10],
		16 : [15, 12, 14, 5 , 11, 37],
		17 : [11, 14, 9 , 6 , 13, 76],
		18 : [17, 14, 11, 7 , 5 , 8 ],
		19 : [18, 15, 12, 16, 7 , 32],
		20 : [19, 16, 14, 9 , 8 , 40],
		21 : [20, 17, 14, 10, 12, 71],
		22 : [21, 18, 15, 13, 20, 2 ],
		23 : [1 , 19, 20, 10, 6 , 13],
		24 : [19, 20, 17, 13, 7 , 34],
		25 : [23, 21, 18, 14, 8 , 51],
		26 : [25, 24, 19, 15, 9 , 68],
		27 : [26, 17, 23, 16, 15, 59],
		28 : [22, 24, 18, 10, 27, 63],
		29 : [28, 25, 26, 18, 12, 14],
		30 : [29, 28, 23, 16, 11, 1 ],
		31 : [30, 29, 24, 27, 26, 6 ],
		32 : [17, 27, 25, 21, 22, 46],
		33 : [32, 29, 15, 22, 16, 38],
		34 : [33, 27, 22, 13, 31, 54],
		35 : [19, 31, 12, 24, 34, 0 ],
		36 : [34, 32, 18, 25, 19, 60],
		37 : [31, 33, 30, 35, 36, 73],
		38 : [23, 34, 31, 30, 10, 21],
		39 : [17, 20, 32, 23, 31, 74],
		40 : [15, 37, 21, 30, 23, 39],
		41 : [33, 39, 40, 30, 22, 42],
		42 : [41, 38, 35, 14, 25, 55],
		43 : [29, 23, 36, 32, 35, 28],
		44 : [43, 24, 18, 42, 36, 65],
		45 : [40, 41, 19, 31, 28, 69],
		46 : [45, 42, 39, 28, 37, 57],
		47 : [38, 41, 40, 43, 44, 17],
		48 : [38, 21, 45, 37, 47, 19],
		49 : [48, 45, 43, 35, 16, 30],
		50 : [49, 46, 43, 39, 33, 9 ],
		51 : [49, 47, 50, 38, 31, 67],
		52 : [51, 48, 45, 41, 32, 5 ],
		53 : [52, 49, 46, 42, 36, 12],
		54 : [49, 50, 45, 42, 44, 4 ],
		55 : [37, 33, 47, 53, 41, 29],
		56 : [40, 52, 50, 45, 39, 61],
		57 : [29, 53, 50, 27, 56, 18],
		58 : [53, 34, 57, 43, 42, 72],
		59 : [58, 44, 52, 48, 53, 22],
		60 : [59, 54, 58, 26, 29, 49],
		61 : [60, 57, 54, 50, 51, 31],
		62 : [38, 48, 55, 34, 61, 43],
		63 : [25, 60, 59, 53, 62, 3 ],
		64 : [48, 39, 46, 53, 57, 52],
		65 : [64, 61, 59, 60, 48, 66],
		66 : [50, 62, 65, 61, 46, 45],
		67 : [66, 41, 62, 38, 57, 75],
		68 : [57, 64, 61, 63, 33, 16],
		69 : [68, 67, 50, 16, 58, 53],
		70 : [61, 66, 63, 56, 29, 33],
		71 : [24, 70, 67, 65, 54, 15],
		72 : [61, 64, 70, 71, 69, 7 ],
		73 : [72, 69, 66, 59, 56, 23],
		74 : [45, 68, 33, 49, 69, 82],
		75 : [67, 66, 72, 7 , 70, 80],
		76 : [25, 67, 73, 69, 63, 81],
		77 : [52, 68, 60, 53, 74, 79],
		78 : [77, 55, 63, 75, 74, 25],
		79 : [76, 76, 61, 78, 51, 48],
		80 : [79, 79, 76, 73, 68, 24],
		81 : [80, 80, 77, 74, 79, 41],
		82 : [81, 81, 80, 75, 71, 50]
	}

	new_state = [ 0 ] * 83
	for i in range( 0, 5 ):
		new_state[ output_combiner[ i ][ 5 ] ] = F( 
			state_components[ output_combiner[ i ][ 0 ] ],
			state_components[ output_combiner[ i ][ 1 ] ],
			state_components[ output_combiner[ i ][ 2 ] ],
			state_components[ output_combiner[ i ][ 3 ] ],
			state_components[ output_combiner[ i ][ 4 ] ],
			i
		)
		new_state[ output_combiner[ i ][ 5 ] ] ^= data_components[ i ]

	for i in range( 5, 10 ):
		new_state[ output_combiner[ i ][ 5 ] ] = F( 
			state_components[ output_combiner[ i ][ 0 ] ],
			state_components[ output_combiner[ i ][ 1 ] ],
			state_components[ output_combiner[ i ][ 2 ] ],
			state_components[ output_combiner[ i ][ 3 ] ],
			state_components[ output_combiner[ i ][ 4 ] ],
			i
		)
		new_state[ output_combiner[ i ][ 5 ] ] ^= data_components[ i ]
		new_state[ output_combiner[ i ][ 5 ] ] ^= state_components[ i ]

	for i in range( 10, 83 ):
		new_state[ output_combiner[ i ][ 5 ] ] = F( 
			state_components[ output_combiner[ i ][ 0 ] ],
			state_components[ output_combiner[ i ][ 1 ] ],
			state_components[ output_combiner[ i ][ 2 ] ],
			state_components[ output_combiner[ i ][ 3 ] ],
			state_components[ output_combiner[ i ][ 4 ] ],
			i
		)
		new_state[ output_combiner[ i ][ 5 ] ] ^= state_components[ i ]

	return "".join( list( map( str, new_state ) ) )


def vest_non_linear_output( data_, state_, key_ = "" ):
	assert len( data_ ) == 10 , "M2 input must have length 10"
	assert len( state_ ) == 83, "M2 state must have length 83"
	assert all( c in '01' for c in data_  ), "M2 input must consist of 0s and 1s"
	assert all( c in '01' for c in state_ ), "M2 state must consist of 0s and 1s"

	state_components = list( map( int, state_ ) )
	output_combiner = {
		0: [ 15, 23, 29, 43, 57, 67 ],
		1: [ 33, 49, 52, 55, 69, 73 ],
		2: [ 17, 22, 45, 60, 61, 72 ],
		3: [ 18, 19, 39, 46, 65, 66 ]
	}
	
	result = ""
	for i in range( 4 ):
		result += str(
				state_components[ output_combiner[ i ][ 0 ] ] ^ \
				state_components[ output_combiner[ i ][ 1 ] ] ^ \
				state_components[ output_combiner[ i ][ 2 ] ] ^ \
				state_components[ output_combiner[ i ][ 3 ] ] ^ \
				state_components[ output_combiner[ i ][ 4 ] ] ^ \
				state_components[ output_combiner[ i ][ 5 ] ]
			)

	return result


def F( q_i0, q_i1, q_i2, q_i3, q_i4, i ):
	transitions = [
		lambda a, b, c, d, e: ~(((((e&a)|c)^e)|((a|d)&b))^(((e&c)^d)&(d^a))),
		lambda a, b, c, d, e: ((((c^d)&b)|(c&e))&(c|a))^(((d|c)^(d&e))|a),
		lambda a, b, c, d, e: ~(((((b|e)^a)&(b|c))|(b^d))^(((e|a)|(c^b))^c)),
		lambda a, b, c, d, e: (((((d|b)&c)^e)|(c^a))^d)^((((d|c)^b)|(d^a))&e),
		lambda a, b, c, d, e: (((c^d)&~e)|((c&d)^b))&(((c^d)^e)|((c^b)^a)),
		lambda a, b, c, d, e: ~((((((a&c)^d)|((d&e)^b))^a)&(c|e))^((d^e)|c)),
		lambda a, b, c, d, e: ~((((e^b)&(e^d))^((b^c)|a))&((((e^b)|a)^c)|d)),
		lambda a, b, c, d, e: ~(((((e^b)|c)^d)|(((e^d)^a)&b))^(((e|c)|(a&d))^a)),
		lambda a, b, c, d, e: ((((e&c)|b)^((e^d)|a))|(((e^a)|b)^d))^(c|d),
		lambda a, b, c, d, e: ((((d|c)&e)|((d&c)^b))^d)^((((d&c)^b)&((d^c)^e))|a),
		lambda a, b, c, d, e: ((((e&c)&d)^a)&((e&b)^d))^((((c^e)|d)^b)|((c|d)&a)),
		lambda a, b, c, d, e: (((a&b)^(e^c))|((a^e)^d))^((((b^a)&d)|(c|e))^b),
		lambda a, b, c, d, e: (((((a&d)&c)|(b^e))^a)|((a^d)&b))^(((d|b)&e)|c),
		lambda a, b, c, d, e: ((((c|e)^a)|((c&e)^d))&(d^b))^(((a|c)|b)^(a&e)),
		lambda a, b, c, d, e: ((((c&a)|b)^c)|(d^e))&~((((b^d)&a)^e)&(e^c)),
		lambda a, b, c, d, e: ~(((((b|d)^(b&a))&e)|(((b^d)&a)^c))^((d^e)|b)),
		lambda a, b, c, d, e: ((((a^b)&d)|c)&(a^e))^(((a|e)&b)^((a|d)^c)),
		lambda a, b, c, d, e: ~(((((((c^e)|a)&c)|((e&b)^d))^a)|((c^d)&b))^(e|d)),
		lambda a, b, c, d, e: ~(((((a|b)&(a^e))|c)&((a&b)|d))^(((e^c)|d)^b)),
		lambda a, b, c, d, e: (((((e&b)^c)|d)^e)|a)^((((e&c)&(d^a))|b)^e),
		lambda a, b, c, d, e: ((((b^e)|a)^c)|((b|d)&e))^(((((b^e)&a)|c)&d)^a),
		lambda a, b, c, d, e: ((((a^c)|e)^b)|((a^b)&d))^(((a&e)^d)&(b^c)),
		lambda a, b, c, d, e: ~(((~((d|b)^(d&a))&e)|c)^((((b&d)|e)&a)^b)),
		lambda a, b, c, d, e: ((((b|e)&d)^c)&((b|a)^c))^((((a|d)^b)|(c&e))^a),
		lambda a, b, c, d, e: ((((c|a)^b)&(b^e))|(e^d))^(((b|e)&c)|(a^d)),
		lambda a, b, c, d, e: (((((a|b)&d)^c)|e)&(((a^b)^d)|c))^(((d|c)^e)|b),
		lambda a, b, c, d, e: (((((a^d)^(e^b))&((a&c)^e))^a)|((d^e)&(b^c)))^d,
		lambda a, b, c, d, e: ~(((((d^e)|(b^a))^c)&(d|b))^(((d&e)^a)&((a^b)|c))),
		lambda a, b, c, d, e: (((((b^c)&a)|d)^b)|(a^e))^(((c|a)^e)&((c&b)|d)),
		lambda a, b, c, d, e: ~(((((d&b)|c)^a)|((c^e)&b))^((((d^c)&a)|(d&e))^e)),
		lambda a, b, c, d, e: (((((b&a)^(e^d))&(e^c))^b)&(((b|a)&d)|e))^(a|d),
		lambda a, b, c, d, e: ~(((((e&b)^a)^((e^d)&c))&((((e^b)&c)|d)^a))^(e^c)),
		lambda a, b, c, d, e: ((((e^a)|d)|(c^b))^e)^(((e&c)|(d^b))&(d^a)),
		lambda a, b, c, d, e: ~(((((d&c)^b)|e)|((d|c)^a))^((((a|d)^b)&(b^c))^a)),
		lambda a, b, c, d, e: ((((e|d)&(b^a))|c)^b)^(((a|c)^d)|((b&e)^c)),
		lambda a, b, c, d, e: (((e|d)&~(c&b))^a)^((((c&e)^b)|a)&(c^d)),
		lambda a, b, c, d, e: ((((b&e)|(c^d))&(b^c))|(((e&c)|a)^e))^(b^e),
		lambda a, b, c, d, e: (((b|c)&(e&a))^((b^e)&d))^((((b^a)|e)^c)|(c&d)),
		lambda a, b, c, d, e: ~((((b&c)^(e^a))&((b&d)|e))^(((e&d)^b)|(c&~a))),
		lambda a, b, c, d, e: (((c|e)&(d^a))|((c^d)^b))^(((c|a)|b)&(d^e)),
		lambda a, b, c, d, e: ((((b&d)^c)|a)^((b^d)&(b^e)))&(((b^c)^e)|(b^a)),
		lambda a, b, c, d, e: (((a|c)&(e&d))^((e^b)&c))^(((d|c)^a)&~((d^e)&b)),
		lambda a, b, c, d, e: ((((b^a)&(d^c))^b)|((b|d)^(c|e)))^((a&e)^d),
		lambda a, b, c, d, e: ((((((b^c)&a)|d)^a)|(b&e))^e)|(((d&e)^b)&(d^c)),
		lambda a, b, c, d, e: ((((e^a)|d)&c)|((e|a)^b))^((e^b)&d),
		lambda a, b, c, d, e: ((((b^e)&a)^b)|((d|c)^a))^((((e&d)^a)&b)|(e^c)),
		lambda a, b, c, d, e: ((((d|b)^a)|(d^c))&(b^e))^((((e&d)|c)&a)^(e^c)),
		lambda a, b, c, d, e: ((((c&a)|d)&e)^((c|b)^a))^(((c&d)^e)&((e^a)|b)),
		lambda a, b, c, d, e: (((((c^d)|b)&(c|a))^e)|(d&e))^(((c^d)|a)^b),
		lambda a, b, c, d, e: ~((~((((e^d)|b)^c)&e)&((c^a)|b))^(d&a)),
		lambda a, b, c, d, e: ((((e^c)&(e^a))|(c&b))^b)|((a^b)&(a^d)),
		lambda a, b, c, d, e: ((((b&c)^(b^e))|((e&a)^d))&((c^a)|b))^(e^a),
		lambda a, b, c, d, e: ((((d|c)^a)&((d^a)^b))|(c^e))^(((d^c)&b)^a),
		lambda a, b, c, d, e: ((((d^a)&c)|e)&(d^b))^(((d&b)|a)^((d^b)|c)),
		lambda a, b, c, d, e: ~((((d|a)^e)|((d&b)|c))^(((a|c)^b)|((b^d)&e))),
		lambda a, b, c, d, e: ~((~(((c^e)|b)&(b^a))&(c^d))|((e^c)&(e^b))),
		lambda a, b, c, d, e: ((((e&d)^c)&(b^a))|((e^c)^b))^(((e|b)^a)&(a|d)),
		lambda a, b, c, d, e: ~(((((a|d)^e)|b)&((e^c)|d))^((((d^e)|c)&(c^b))|a)),
		lambda a, b, c, d, e: ~((((d^e)|b)&~((b^c)&d))^((((d|c)&(b^e))^b)&a)),
		lambda a, b, c, d, e: ~(((((c&e)|a)^d)|((a^b)&e))^((((e|d)&(c^a))|b)^c)),
		lambda a, b, c, d, e: (((((d^c)&b)|a)^((d&c)|b))|(((d|c)&a)^e))^d,
		lambda a, b, c, d, e: (((((e^d)|b)^c)|(c^a))&((((e^c)&b)^a)|d))^(e^c),
		lambda a, b, c, d, e: (((e^a)&(e^d))|((a^b)^c))&(((d|e)^b)|((d&a)|c)),
		lambda a, b, c, d, e: (((a&c)|(a^b))&~d)|(((a&b)^(a^e))&(e^c)),
		lambda a, b, c, d, e: ((((b^e)&a)^(c^d))|((c&d)^e))^((((e|c)^a)&d)|b),
		lambda a, b, c, d, e: ((((((c&d)|a)^b)&e)^(c|e))&(d|b))^((d^b)|a),
		lambda a, b, c, d, e: (((((a^d)&e)|c)^a)|(d^b))^((((a|c)^e)|d)^a),
		lambda a, b, c, d, e: ((((((e|c)^a)&d)^e)|(c^b))^a)|((e&c)&(d^b)),
		lambda a, b, c, d, e: ~(((((c|e)^d)&b)|((c^d)^a))&~(((e|a)^b)&(e^c))),
		lambda a, b, c, d, e: (((((c^e)|d)&c)^b)|a)^((((b&c)^a)|e)&(b^d)),
		lambda a, b, c, d, e: ~(((((e|c)^a)&~((e^b)&d))|(c&d))^(e&b)),
		lambda a, b, c, d, e: (((((a^c)^b)&((a^d)^e))^c)|((c^d)&~b))^e,
		lambda a, b, c, d, e: ((((e&d)|c)&((e^a)^b))^d)^(((((e^d)^c)&a)^e)|b),
		lambda a, b, c, d, e: ((((e^c)|a)^((d^b)&c))&((((a^d)|c)^b)|e))^(a&d),
		lambda a, b, c, d, e: ((((c|a)^e)&(c|d))|(e^b))^((((a&e)^c)&(d^b))^a),
		lambda a, b, c, d, e: (((e|c)&(b^a))|((e|b)^d))^((((b^e)|d)^(b&c))&a),
		lambda a, b, c, d, e: ((((c&e)|b)^d)|((c|a)^d))^((((c^b)&a)|(d|e))^a),
		lambda a, b, c, d, e: ~(((((a^b)&c)^a)&((c^d)|e))^(((e&~b)|(a^d))^c)),
		lambda a, b, c, d, e: (((e^c)|(d^b))^((e^a)|c))|(((e|a)|(b&c))^(b|d)),
		lambda a, b, c, d, e: ~(((((b&d)^(e^a))&(b|c))|(((b&e)^c)&(c^d)))^(e|a)),
		lambda a, b, c, d, e: (((((e&a)|d)&((e&c)^b))^a)|((c^e)&(c^d)))^b,
		lambda a, b, c, d, e: ~(((((d^c)|e)|(a^b))&d)^(((a|b)^c)|((a^d)&e))),
		lambda a, b, c, d, e: (((((e|a)^d)&(e^b))^a)&(((e&d)^b)|c))^((d|c)^b)
	]

	return transitions[ i ]( q_i0, q_i1, q_i2, q_i3, q_i4 ) & 1



# 1111001010111011 - data example

# VEST Linear
# 1010111011 - initial state example
# vest_linear_transition - transition function
# vest_linear_output - output function

# VEST Non Linear
# 11101101100010011011110011101000001100100001010001001101000010111000101111010000111 - initial state example
# vest_non_linear_transition - transition function
# vest_non_linear_output - output function