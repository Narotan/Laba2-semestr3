package array

import "strings"

type Array struct {
	data     []*string
	size     int
	capacity int
}

func NewArray() *Array {
	cap := 4
	return &Array{
		data:     make([]*string, cap),
		size:     0,
		capacity: cap,
	}
}

func (a *Array) Size() int {
	return a.size
}

func (a *Array) Empty() bool {
	return a.size == 0
}

func (a *Array) resize() {
	newCap := a.capacity * 2
	newData := make([]*string, newCap)
	copy(newData, a.data[:a.size])
	a.data = newData
	a.capacity = newCap
}

func (a *Array) Append(value string) {
	if a.size >= a.capacity {
		a.resize()
	}
	str := new(string)
	*str = value
	a.data[a.size] = str
	a.size++
}

func (a *Array) Insert(index int, value string) {
	if index < 0 || index > a.size {
		return
	}
	if a.size >= a.capacity {
		a.resize()
	}
	for i := a.size; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	str := new(string)
	*str = value
	a.data[index] = str
	a.size++
}

func (a *Array) Get(index int) string {
	if index < 0 || index >= a.size {
		return ""
	}
	return *a.data[index]
}

func (a *Array) Set(index int, value string) {
	if index < 0 || index >= a.size {
		return
	}
	*a.data[index] = value
}

func (a *Array) Remove(index int) {
	if index < 0 || index >= a.size {
		return
	}
	for i := index; i < a.size-1; i++ {
		a.data[i] = a.data[i+1]
	}
	a.data[a.size-1] = nil
	a.size--
}

func (a *Array) RemoveByValue(value string) bool {
	for i := 0; i < a.size; i++ {
		if a.data[i] != nil && strings.Compare(*a.data[i], value) == 0 {
			a.Remove(i)
			return true
		}
	}
	return false
}
