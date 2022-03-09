#ifndef FINITE_AUTOMATON_H
#define FINITE_AUTOMATON_H

template <
	typename In,		// input type
	typename Out,		// output type
	typename State,		// state type
	typename TransFunc,	// transition function
	typename OutFunc	// output function
>
class FiniteAutomaton {
public:
	FiniteAutomaton(const State& init,
			const TransFunc& trf,
			const OutFunc& outf);
	FiniteAutomaton& operator =(const FiniteAutomaton& other);

	State get_state() const { return curr_state; }
	Out step(const In& word);

protected:
	State curr_state;
	TransFunc transform;
	OutFunc output;
};

// function for auto deducing types TransFunc and OutFunc
template <typename In, typename Out, typename State,
	typename TransFunc, typename OutFunc>
FiniteAutomaton<In, Out, State, TransFunc, OutFunc> make_automaton(
		const State& init,
		const TransFunc& trf,
		const OutFunc& outf) {
	return {init, trf, outf};
}

//-----------------------IMPLEMENTATION---------------------------

template <typename In, typename Out, typename State,
	typename TransFunc, typename OutFunc>
FiniteAutomaton<In, Out, State, TransFunc, OutFunc>::FiniteAutomaton(
		const State& init,
		const TransFunc& trf,
		const OutFunc& outf) :
	curr_state{init}, transform{trf}, output{outf} {}

template <typename In, typename Out, typename State,
	typename TransFunc, typename OutFunc>
FiniteAutomaton<In, Out, State, TransFunc, OutFunc>&
FiniteAutomaton<In, Out, State, TransFunc, OutFunc>::operator =(
		const FiniteAutomaton& other) {
	if (this == &other)
		return *this;
	curr_state = other.curr_state;
	transform = other.transform;
	output = other.output;
	return *this;
}

template <typename In, typename Out, typename State,
	typename TransFunc, typename OutFunc>
Out FiniteAutomaton<In, Out, State, TransFunc, OutFunc>::step(const In& word) {
	Out ret = output(word, curr_state);
	curr_state = transform(word, curr_state);
	return ret;
}

#endif
