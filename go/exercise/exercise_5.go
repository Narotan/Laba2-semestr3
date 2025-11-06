package exercises

import (
	"laba2/structs/huffman"
)

// HuffmanEncodeDecode выполняет кодирование и декодирование строки с помощью алгоритма Хаффмана
func HuffmanEncodeDecode(text string) (encoded string, decoded string, tree *huffman.HuffmanTree) {
	// Создаем дерево Хаффмана на основе входной строки
	tree = huffman.NewHuffmanTree(text)

	encoded = tree.Encode(text)

	decoded = tree.Decode(encoded)

	return encoded, decoded, tree
}
