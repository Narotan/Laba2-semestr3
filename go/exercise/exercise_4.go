package exercises

import "laba2/structs/array"

func SequenceCheck(template *array.Array, sequence *array.Array) bool {
	left := 0  // индекс шаблона
	right := 0 // индекс последовательности

	lastStarPos := -1
	rightBack := -1

	for right < sequence.Size() {
		tChar := template.Get(left)
		sChar := sequence.Get(right)

		if left < template.Size() && (tChar == sChar || tChar == "?") {
			left++
			right++
		} else if left < template.Size() && tChar == "*" {
			lastStarPos = left
			rightBack = right
			left++
		} else if lastStarPos != -1 {
			left = lastStarPos + 1
			rightBack++
			right = rightBack
		} else {
			return false
		}
	}

	for left < template.Size() && template.Get(left) == "*" {
		left++
	}

	return left == template.Size()
}
