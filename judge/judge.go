package main

import (
	"fmt"
	"log"
	"net/http"
	"os/exec"
	"path/filepath"

	"github.com/gin-gonic/gin"
)

func gameRunner(path string, metafile string) {
	cmd := exec.Command(filepath.Join(path, "run"), filepath.Join(path, metafile))
	stdout, err := cmd.Output()

	if err != nil {
		fmt.Println("Error")
		return
	}

	fmt.Println(string(stdout))
}

func get(c *gin.Context) {
	fmt.Println("ping")
}

func submit(c *gin.Context) {
	file, err := c.FormFile("submission")
	if err != nil {
		log.Println(err)
		c.Status(500)
		return
	}
	c.SaveUploadedFile(file, "submission.cpp")

	c.Status(http.StatusOK)
}

func main() {
	// var gamePath string
	// flag.StringVar(&gamePath, "p", "", "Game Dir Path")
	// flag.Parse()

	// metaFiles := [1]string{"sample_metafile"}
	// for _, metafile := range metaFiles {
	// 	gameRunner(gamePath, metafile)
	// }

	r := gin.Default()
	r.MaxMultipartMemory = 8 << 20 //8Mib
	r.GET("/", get)
	r.POST("/submit", submit)

	r.Run()
}
