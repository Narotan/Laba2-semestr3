package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"

	testTask "laba2/tests"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Println("\n========================================")
		fmt.Println("Выберите номер задания:")
		fmt.Println("========================================")
		fmt.Println("1 - Логические выражения")
		fmt.Println("2 - Работа с множеством (HashSet) Union")
		fmt.Println("3 - Работа с множеством (HashSet) Intersection")
		fmt.Println("4 - Работа с множеством (HashSet) Difference")
		fmt.Println("5 - Алгоритм Хаффмана (кодирование/декодирование)")
		fmt.Println("6 - LRU кэш")
		fmt.Println("0 - Выход")
		fmt.Println("========================================")
		fmt.Print("Ваш выбор: ")

		input, _ := reader.ReadString('\n')
		input = strings.TrimSpace(input)
		choice, err := strconv.Atoi(input)
		if err != nil {
			fmt.Println("Некорректный ввод. Введите число.")
			continue
		}

		switch choice {
		case 1:
			testTask.RunLogicExpression()
		case 2:
			testTask.RunHashSetUnion()
		case 3:
			testTask.RunHashSetIntersection()
		case 4:
			testTask.RunHashSetDifference()
		case 5:
			testTask.RunHuffmanEncoding()
		case 6:
			testTask.RunLRUCache()
		case 0:
			fmt.Println("Выход из программы.")
			return
		default:
			fmt.Println("Неверный выбор. Попробуйте снова.")
		}

	}
}
