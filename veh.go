package main

import (
	"fmt"
	"os"
	"syscall"
)

func main() {
	dll := syscall.MustLoadDLL("veh.dll")
	RaiseExcept := dll.MustFindProc("RaiseExcept")
	RaiseNoExcept := dll.MustFindProc("RaiseNoExcept")
	ThreadRaiseExcept := dll.MustFindProc("ThreadRaiseExcept")
	ThreadRaiseNoExcept := dll.MustFindProc("ThreadRaiseNoExcept")
	fmt.Println("initialized")

	thread := false
	if 2 <= len(os.Args) && "thread" == os.Args[1] {
		thread = true
	}

	if !thread {
		RaiseExcept.Call()
		fmt.Println("returned from RaiseExcept")

		RaiseNoExcept.Call()
		fmt.Println("oops: returned from RaiseNoExcept")
	} else {
		ThreadRaiseExcept.Call()
		fmt.Println("returned from ThreadRaiseExcept")

		ThreadRaiseNoExcept.Call()
		fmt.Println("oops: returned from ThreadRaiseNoExcept")
	}
}
