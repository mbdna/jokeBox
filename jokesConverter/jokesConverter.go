package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"strconv"
	"strings"
)

var joke = ""
var answer = ""

func main() {

	file, err := ioutil.ReadFile("jokes2.txt") // just pass the file name
	if err != nil {
	}

	str := string(file)
	lines := strings.Split(str, "\n")

	for x, line := range lines {

		if joke != "" && answer != "" {
			list := ""
			list = list + "file " + joke + "\n"
			list = list + "file silence.wav\n"
			list = list + "file " + answer

			fi, e := os.Create("list.txt")
			if e != nil {
			}
			fi.WriteString(list)
			fi.Sync()
			joke = ""
			answer = ""
			app := "ffmpeg"
			arg0 := "-f"
			arg1 := "concat"
			arg2 := "-safe"
			arg3 := "0"
			arg4 := "-i"
			arg5 := "list.txt"
			arg6 := "-c"
			arg7 := "copy"
			arg8 := "fullJoke" + strconv.Itoa(x) + ".wav"
			exec.Command(app, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8).Start()

		}

		if x%2 == 0 {
			fmt.Println("joke: " + line)
			app := "pico2wave"
			arg0 := "-w=joke" + strconv.Itoa(x) + ".wav"
			joke = "joke" + strconv.Itoa(x) + ".wav"
			arg1 := "\"" + line + "\""
			exec.Command(app, arg0, arg1).Start()
		} else {
			fmt.Println("answer: " + line)
			app := "pico2wave"
			arg0 := "-w=answer" + strconv.Itoa(x-1) + ".wav"
			answer = "answer" + strconv.Itoa(x-1) + ".wav"
			arg1 := "\"" + line + "\""
			exec.Command(app, arg0, arg1).Start()
		}

	}

}
