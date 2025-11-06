package testTask

import (
	"fmt"
	exercises "laba2/exercise"
	"laba2/structs/set"
)

func RunLogicExpression() {
	expres := "((!1 | 0) & (1 ^ 0))"
	result, err := exercises.LogicExpWithStack(expres)
	if err != nil {
		fmt.Println("error: problem with calculation:", err)
		return
	}
	fmt.Println("asnwer:", result)
}

func RunHashSetUnion() {
	mainSet := set.NewHashSet(11)
	otherSet := set.NewHashSet(11)
	numbers1 := []string{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"}
	numbers2 := []string{"11", "12", "13", "14", "15", "16", "17", "18", "19", "20"}

	for _, n := range numbers1 {
		mainSet.Add(n)
	}
	fmt.Println("main set: ")
	mainSet.Print()

	for _, n := range numbers2 {
		otherSet.Add(n)
	}
	fmt.Println("other set: ")
	otherSet.Print()

	fmt.Println("main set after Union operation: ")
	mainSet.Union(otherSet)

	mainSet.Print()
}

func RunHashSetIntersection() {
	mainSet := set.NewHashSet(11)
	otherSet := set.NewHashSet(11)
	numbers1 := []string{"1", "2", "3", "4", "5"}
	numbers2 := []string{"11", "12", "3", "15", "1"}

	for _, n := range numbers1 {
		mainSet.Add(n)
	}
	fmt.Println("main set: ")
	mainSet.Print()

	for _, n := range numbers2 {
		otherSet.Add(n)
	}
	fmt.Println("other set: ")
	otherSet.Print()

	fmt.Println("main set after Intersection operation: ")
	newSet := mainSet.Intersection(otherSet)

	newSet.Print()
}

func RunHashSetDifference() {
	mainSet := set.NewHashSet(11)
	otherSet := set.NewHashSet(11)
	numbers1 := []string{"1", "2", "3", "4", "5"}
	numbers2 := []string{"11", "12", "3", "15", "1"}

	for _, n := range numbers1 {
		mainSet.Add(n)
	}
	fmt.Println("main set: ")
	mainSet.Print()

	for _, n := range numbers2 {
		otherSet.Add(n)
	}
	fmt.Println("other set: ")
	otherSet.Print()

	fmt.Println("main set after Difference operation: ")
	newSet := mainSet.Difference(otherSet)

	newSet.Print()
}

func RunHuffmanEncoding() {
	fmt.Println("\n=== Тест алгоритма Хаффмана ===")

	testString := "abracadabra"
	fmt.Printf("\nИсходная строка: %s\n", testString)

	encoded, decoded, tree := exercises.HuffmanEncodeDecode(testString)

	fmt.Println("\nКоды символов:")
	tree.PrintCodes()

	fmt.Println("\nРезультаты кодирования:")
	fmt.Printf("  Закодированная строка: %s\n", encoded)
	fmt.Printf("  Длина закодированной строки: %d бит\n", len(encoded))
	fmt.Printf("  Декодированная строка: %s\n", decoded)

	if testString == decoded {
		fmt.Println("✓ Декодирование успешно! Строки совпадают.")
	} else {
		fmt.Println("✗ Ошибка декодирования! Строки не совпадают.")
	}

	originalBits := len(testString) * 8
	compressedBits := len(encoded)
	ratio := tree.GetCompressionRatio(testString)

	fmt.Println("\nСтатистика сжатия:")
	fmt.Printf("  Оригинальный размер: %d бит (%d символов * 8 бит)\n", originalBits, len(testString))
	fmt.Printf("  Сжатый размер: %d бит\n", compressedBits)
	fmt.Printf("  Коэффициент сжатия: %.2f\n", ratio)
	fmt.Printf("  Экономия места: %.2f%%\n", (1-1/ratio)*100)

	fmt.Println("\n=== Дополнительные примеры ===")
	testCases := []string{
		"hello world",
		"aaaaabbbbbcccccddddd",
		"Go programming language",
	}

	for i, test := range testCases {
		fmt.Printf("\nПример %d: %s\n", i+1, test)
		enc, dec, t := exercises.HuffmanEncodeDecode(test)
		fmt.Println("  Коды символов:")
		t.PrintCodes()
		fmt.Printf("  Закодировано: %s\n", enc)
		fmt.Printf("  Декодировано: %s\n", dec)
		fmt.Printf("  Совпадает с исходной строкой: %v\n", test == dec)
		fmt.Printf("  Коэффициент сжатия: %.2f\n", t.GetCompressionRatio(test))
	}
}

func RunLRUCache() {
	queries := []exercises.Query{
		exercises.CreateQuery("SET", 1, 2),
		exercises.CreateQuery("SET", 2, 3),
		exercises.CreateQuery("SET", 1, 5),
		exercises.CreateQuery("SET", 4, 5),
		exercises.CreateQuery("SET", 6, 7),
		exercises.CreateQuery("GET", 4, 0),
		exercises.CreateQuery("SET", 1, 2),
		exercises.CreateQuery("GET", 3, 0),
	}

	results := exercises.RunLRUCache(2, queries)

	fmt.Println("asnwer:", results)
}
