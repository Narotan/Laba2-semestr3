package exercises

import (
	"fmt"
	"laba2/structs/lru"
)

// Query представляет один запрос к LRU кэшу
type Query struct {
	operation string
	key       int
	value     int
}

// RunLRUCache выполняет серию запросов к LRU кэшу
func RunLRUCache(capacity int, queries []Query) []int {
	cache := lru.NewLRUCache(capacity)
	results := make([]int, 0)

	fmt.Printf("Инициализация LRU кэша с емкостью: %d\n", capacity)
	fmt.Println("========================================")

	for i, query := range queries {
		if query.operation == "SET" {
			fmt.Printf("Запрос %d: SET %d %d\n", i+1, query.key, query.value)
			cache.Set(query.key, query.value)
			cache.Print()
		} else if query.operation == "GET" {
			result := cache.Get(query.key)
			fmt.Printf("Запрос %d: GET %d -> %d\n", i+1, query.key, result)
			results = append(results, result)
			cache.Print()
		}
		fmt.Println("----------------------------------------")
	}

	return results
}

// CreateQuery создает новый запрос
func CreateQuery(operation string, key int, value int) Query {
	return Query{
		operation: operation,
		key:       key,
		value:     value,
	}
}
