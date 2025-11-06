package stack

import "fmt"

type Node struct {
	value string
	next  *Node
}

type Stack struct {
	top *Node
}

func (s *Stack) Push(value string) {
	newNode := &Node{
		value: value,
		next:  s.top,
	}
	s.top = newNode
}

func (s *Stack) Pop() (string, bool) {
	if s.top == nil {
		return "", false
	}

	value := s.top.value
	s.top = s.top.next
	return value, true
}

func (s *Stack) Peek() (string, bool) {
	if s.top == nil {
		return "", false
	}
	return s.top.value, true
}

func (s *Stack) IsEmpty() bool {
	return s.top == nil
}

func (s *Stack) PrintAll() {
	if s.top == nil {
		fmt.Println("[]")
		return
	}

	var values []string
	current := s.top
	for current != nil {
		values = append([]string{current.value}, values...)
		current = current.next
	}
	fmt.Println(values)
}

func (s *Stack) String() string {
	if s.top == nil {
		return "[]"
	}

	var values []string
	current := s.top
	for current != nil {
		values = append([]string{current.value}, values...)
		current = current.next
	}
	return fmt.Sprint(values)
}
