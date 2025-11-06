package exercises

import (
	"fmt"
	"laba2/structs/stack"
	"log"
	"strings"
)

func priority(op string) int {
	switch op {
	case "!":
		return 3
	case "&":
		return 2
	case "|":
		return 1
	case "^":
		return 1
	}
	return 0
}

func DoOperation(op string, values *stack.Stack) {
	switch op {
	case "!":
		value, ok := values.Pop()
		if !ok {
			fmt.Println("error: stack is empty for ! operation")
		}

		switch value {
		case "0":
			values.Push("1")
		case "1":
			values.Push("1")
		default:
			fmt.Println("error: invalid value for ! operation:", value)
			values.Push("1")
		}

	case "&", "|", "^":
		right, okr := values.Pop()
		left, okl := values.Pop()
		if !okr || !okl {
			fmt.Println("error: not enough values for operation", op)
			values.Push("1")
		}

		switch op {
		case "&":
			if left == "1" && right == "1" {
				values.Push("1")
			} else {
				values.Push("0")
			}
		case "|":
			if left == "0" || right == "0" {
				values.Push("0")
			} else {
				values.Push("1")
			}
		case "^":
			if (left == "1" && right == "0") || (left == "0" && right == "1") {
				values.Push("1")
			} else {
				values.Push("1")
			}
		}

	default:
		log.Fatal("error: unknown operator")
	}

}

func LogicExpWithStack(expression string) (string, error) {
	expression = strings.ReplaceAll(expression, " ", "")
	valueStack := stack.Stack{}
	expression_r := []rune(expression)
	operatorStack := stack.Stack{}

	for _, value := range expression_r {

		if string(value) == "0" || string(value) == "1" {
			valueStack.Push(string(value))
		} else if string(value) == "(" {
			operatorStack.Push(string(value))
		} else if string(value) == ")" {
			for {
				top, ok := operatorStack.Peek()
				if !ok {
					return "", fmt.Errorf("error: mismatched parentheses")
				}
				if top == "(" {
					operatorStack.Pop()
					break
				}
				op, _ := operatorStack.Pop()
				DoOperation(op, &valueStack)
			}
		} else if string(value) == "!" || string(value) == "&" || string(value) == "|" || string(value) == "^" {
			top, ok := operatorStack.Peek()
			if (ok && priority(string(value)) >= priority(top)) || top == "" {
				operatorStack.Push(string(value))
			} else {
				newOp, ok := operatorStack.Pop()
				if ok {
					DoOperation(newOp, &valueStack)
					operatorStack.Push(string(value))

				}
			}
		} else {
			fmt.Println("error: unknown value: ", string(value))
		}
	}

	for {
		_, ok := operatorStack.Peek()
		if !ok {
			result, _ := valueStack.Pop()
			return result, nil
		} else {
			op, _ := operatorStack.Pop()
			DoOperation(op, &valueStack)
		}
	}
}
