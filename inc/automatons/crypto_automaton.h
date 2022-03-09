#ifndef CRYPTO_AUTOMATON_H
#define CRYPTO_AUTOMATON_H

#include "finite_automaton.h"

// crypto automaton is an automaton with a key
template <
	typename In,		// input type
	typename Out,		// output type
	typename State,		// state type
	typename TransFunc,	// transition function
	typename OutFunc,	// output function
	typename KeyType	// key of crypto automaton
>
class CryptoAutomaton:
	public FiniteAutomaton<In, Out, State, TransFunc, OutFunc> {
public:
	CryptoAutomaton(const State& init,
			const KeyType& init_key,
			const TransFunc& trf,
			const OutFunc& outf);
	CryptoAutomaton& operator =(const CryptoAutomaton& other);

	Out step(const In& word);
	KeyType get_key() const { return key; }
private:
	KeyType key;
};

// function for auto deducing types TransFunc and OutFunc
template <typename In, typename Out, typename KeyType, typename State,
	typename TransFunc, typename OutFunc>
CryptoAutomaton<In, Out, State, TransFunc, OutFunc, KeyType> make_crypto(
		const State& init,
		const KeyType& init_key,
		const TransFunc& trf,
		const OutFunc& outf) {
	return {init, init_key, trf, outf};
}

//-----------------------IMPLEMENTATION---------------------------

template <typename In, typename Out, typename State,
	typename TransFunc, typename OutFunc, typename KeyType>
CryptoAutomaton<In, Out, State, TransFunc, OutFunc, KeyType>::CryptoAutomaton(
		const State& init,
		const KeyType& init_key,
		const TransFunc& trf,
		const OutFunc& outf) :
	FiniteAutomaton<In, Out, State, TransFunc, OutFunc>::
		FiniteAutomaton(init, trf, outf), key{init_key} {}

template <typename In, typename Out, typename State,
	typename TransFunc, typename OutFunc, typename KeyType>
CryptoAutomaton<In, Out, State, TransFunc, OutFunc, KeyType>&
CryptoAutomaton<In, Out, State, TransFunc, OutFunc, KeyType>::operator =(
		const CryptoAutomaton& other) {
	if (this == &other)
		return *this;
	FiniteAutomaton<In, Out, State, TransFunc, OutFunc>::operator =(other);
	key = other.key;
	return *this;
}

template <typename In, typename Out, typename State,
	typename TransFunc, typename OutFunc, typename KeyType>
Out CryptoAutomaton<In, Out, State, TransFunc, OutFunc, KeyType>::
step(const In& word) {
	Out ret = this->output(word, this->curr_state, key);
	this->curr_state = this->transform(word, this->curr_state, key);
	return ret;
}

#endif
