package huffman

import (
	"container/heap"
	"fmt"
	"strings"
)

type Node struct {
	Char      rune
	Frequency int
	Left      *Node
	Right     *Node
}

type PriorityQueue []*Node

// реализуем интерфейс для heap
func (pq PriorityQueue) Len() int {
	return len(pq)
}

func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].Frequency < pq[j].Frequency
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}

func (pq *PriorityQueue) Push(x interface{}) {
	*pq = append(*pq, x.(*Node))
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	node := old[n-1]
	*pq = old[0 : n-1]
	return node
}

type HuffmanTree struct {
	Root  *Node
	Codes map[rune]string
}

func NewHuffmanTree(text string) *HuffmanTree {
	if text == "" {
		return &HuffmanTree{
			Root:  nil,
			Codes: make(map[rune]string),
		}
	}

	frequencies := make(map[rune]int)
	for _, char := range text {
		frequencies[char]++
	}

	pq := make(PriorityQueue, 0, len(frequencies))
	for char, freq := range frequencies {
		pq = append(pq, &Node{
			Char:      char,
			Frequency: freq,
			Left:      nil,
			Right:     nil,
		})
	}

	heap.Init(&pq)

	// строим дерево
	for pq.Len() > 1 {
		left := heap.Pop(&pq).(*Node)
		right := heap.Pop(&pq).(*Node)

		parent := &Node{
			Char:      0,
			Frequency: left.Frequency + right.Frequency,
			Left:      left,
			Right:     right,
		}

		heap.Push(&pq, parent)
	}

	root := heap.Pop(&pq).(*Node)

	tree := &HuffmanTree{
		Root:  root,
		Codes: make(map[rune]string),
	}

	tree.generateCodes(root, "")

	return tree
}

func (ht *HuffmanTree) generateCodes(node *Node, code string) {
	if node == nil {
		return
	}

	// Если это лист, сохраняем код
	if node.Left == nil && node.Right == nil {
		ht.Codes[node.Char] = code
		return
	}

	// Рекурсивно обходим дерево
	ht.generateCodes(node.Left, code+"0")
	ht.generateCodes(node.Right, code+"1")
}

func (ht *HuffmanTree) Encode(text string) string {
	if ht.Root == nil {
		return ""
	}

	var encoded strings.Builder
	for _, char := range text {
		if code, exists := ht.Codes[char]; exists {
			encoded.WriteString(code)
		}
	}
	return encoded.String()
}

func (ht *HuffmanTree) Decode(encoded string) string {
	if ht.Root == nil || encoded == "" {
		return ""
	}

	var decoded strings.Builder
	current := ht.Root

	for _, bit := range encoded {
		if bit == '0' {
			current = current.Left
		} else if bit == '1' {
			current = current.Right
		}

		if current.Left == nil && current.Right == nil {
			decoded.WriteRune(current.Char)
			current = ht.Root
		}
	}

	return decoded.String()
}

func (ht *HuffmanTree) PrintCodes() {
	if len(ht.Codes) == 0 {
		fmt.Println("Нет кодов для отображения")
		return
	}

	fmt.Println("Коды символов Хаффмана:")
	for char, code := range ht.Codes {
		fmt.Printf("%c: %s\n", char, code)
	}
}

func (ht *HuffmanTree) PrintTree() {
	fmt.Println("Дерево Хаффмана:")
	ht.printNode(ht.Root, "")
}

func (ht *HuffmanTree) printNode(node *Node, prefix string) {
	if node == nil {
		return
	}

	if node.Left == nil && node.Right == nil {
		fmt.Printf("%s'%c' (freq: %d)\n", prefix, node.Char, node.Frequency)
		return
	}

	fmt.Printf("%s* (freq: %d)\n", prefix, node.Frequency)

	if node.Left != nil {
		ht.printNode(node.Left, prefix+"  ")
	}
	if node.Right != nil {
		ht.printNode(node.Right, prefix+"  ")
	}
}

func (ht *HuffmanTree) GetCompressionRatio(originalText string) float64 {
	if originalText == "" {
		return 0
	}

	originalBits := len(originalText) * 8
	encodedBits := len(ht.Encode(originalText))

	if encodedBits == 0 {
		return 0
	}

	return float64(originalBits) / float64(encodedBits)
}
