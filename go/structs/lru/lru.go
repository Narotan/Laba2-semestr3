package lru

import "fmt"

type Node struct {
	key   int
	value int
	prev  *Node
	next  *Node
}

type LRUCache struct {
	capacity int
	size     int
	cache    map[int]*Node
	head     *Node
	tail     *Node
}

func NewLRUCache(capacity int) *LRUCache {
	head := &Node{}
	tail := &Node{}
	head.next = tail
	tail.prev = head

	return &LRUCache{
		capacity: capacity,
		size:     0,
		cache:    make(map[int]*Node),
		head:     head,
		tail:     tail,
	}
}

func (lru *LRUCache) addToHead(node *Node) {
	node.prev = lru.head
	node.next = lru.head.next
	lru.head.next.prev = node
	lru.head.next = node
}

func (lru *LRUCache) removeNode(node *Node) {
	node.prev.next = node.next
	node.next.prev = node.prev
}

func (lru *LRUCache) moveToHead(node *Node) {
	lru.removeNode(node)
	lru.addToHead(node)
}

func (lru *LRUCache) removeTail() *Node {
	node := lru.tail.prev
	lru.removeNode(node)
	return node
}

func (lru *LRUCache) Set(key int, value int) {
	node, exists := lru.cache[key]

	if exists {
		node.value = value
		lru.moveToHead(node)
	} else {
		newNode := &Node{
			key:   key,
			value: value,
		}

		lru.cache[key] = newNode
		lru.addToHead(newNode)
		lru.size++

		if lru.size > lru.capacity {
			tail := lru.removeTail()
			delete(lru.cache, tail.key)
			lru.size--
		}
	}
}

func (lru *LRUCache) Get(key int) int {
	node, exists := lru.cache[key]

	if !exists {
		return -1
	}

	lru.moveToHead(node)
	return node.value
}

func (lru *LRUCache) Print() {
	fmt.Print("Кэш (от недавних к старым): ")
	current := lru.head.next
	first := true
	for current != lru.tail {
		if !first {
			fmt.Print(", ")
		}
		fmt.Printf("%d -> %d", current.key, current.value)
		current = current.next
		first = false
	}
	fmt.Println()
}

func (lru *LRUCache) Size() int {
	return lru.size
}

func (lru *LRUCache) Capacity() int {
	return lru.capacity
}
