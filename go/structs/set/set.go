package set

import (
	"fmt"
	"hash/fnv"
)

type node struct {
	value string
	next  *node
}

type HashSet struct {
	buckets []*node
	size    int
}

func NewHashSet(capacity int) *HashSet {
	return &HashSet{
		buckets: make([]*node, capacity),
		size:    0,
	}
}

func hash(s string) uint32 {
	h := fnv.New32a()
	h.Write([]byte(s))
	return h.Sum32()
}

func (set *HashSet) Add(value string) {
	if set.Contains(value) {
		return
	}

	if float64(set.size)/float64(len(set.buckets)) > 0.75 {
		set.rehash()
	}

	index := int(hash(value)) % len(set.buckets)
	newNode := &node{value: value, next: set.buckets[index]}
	set.buckets[index] = newNode
	set.size++
}

func (set *HashSet) Contains(value string) bool {
	index := int(hash(value)) % len(set.buckets)
	current := set.buckets[index]
	for current != nil {
		if current.value == value {
			return true
		}
		current = current.next
	}
	return false
}

func (set *HashSet) Remove(value string) {
	index := int(hash(value)) % len(set.buckets)
	current := set.buckets[index]
	var prev *node

	for current != nil {
		if current.value == value {
			if prev == nil {
				set.buckets[index] = current.next
			} else {
				prev.next = current.next
			}
			set.size--
			return
		}
		prev = current
		current = current.next
	}
}

func (set *HashSet) rehash() {
	oldBuckets := set.buckets
	newBuckets := make([]*node, len(oldBuckets)*2)

	for _, bucket := range oldBuckets {
		current := bucket
		for current != nil {
			index := int(hash(current.value)) % len(newBuckets)
			newNode := &node{value: current.value, next: newBuckets[index]}
			newBuckets[index] = newNode
			current = current.next
		}
	}

	set.buckets = newBuckets
}

func (set *HashSet) Print() {
	for i, bucket := range set.buckets {
		fmt.Printf("[%d]: ", i)
		current := bucket
		for current != nil {
			fmt.Printf("%s -> ", current.value)
			current = current.next
		}
		fmt.Println("nil")
	}
}

// ex 3 variant 3

func (set *HashSet) Union(other *HashSet) *HashSet {
	for _, bucket := range other.buckets {
		current := bucket
		for current != nil {
			set.Add(current.value)
			current = current.next
		}
	}

	return set
}

func (set *HashSet) Intersection(other *HashSet) *HashSet {
	newSet := NewHashSet(set.size)

	for _, bucket := range set.buckets {
		current := bucket
		for current != nil {
			if other.Contains(current.value) {
				newSet.Add(current.value)
			}
			current = current.next
		}
	}
	return newSet
}

func (set *HashSet) Difference(other *HashSet) *HashSet {
	newSet := NewHashSet(set.size)

	for _, bucket := range set.buckets {
		current := bucket
		for current != nil {
			if set.Contains(current.value) && !other.Contains(current.value) {
				newSet.Add(current.value)
			}
			current = current.next
		}
	}
	return newSet
}
