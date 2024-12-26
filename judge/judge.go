package main

import (
	"context"
	"fmt"
	"log"
	"net/http"
	"os/exec"
	"path/filepath"
	"time"

	"github.com/gin-gonic/gin"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

func connect(uri string) (*mongo.Client, context.Context,
	context.CancelFunc, error) {

	ctx, cancel := context.WithTimeout(context.Background(),
		30*time.Second)

	client, err := mongo.Connect(ctx, options.Client().ApplyURI(uri))
	return client, ctx, cancel, err
}

func close(client *mongo.Client, ctx context.Context,
	cancel context.CancelFunc) {

	defer cancel()

	defer func() {
		if err := client.Disconnect(ctx); err != nil {
			panic(err)
		}
	}()
}

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

	client, ctx, cancel, err := connect("mongodb://localhost:27017")
	if err != nil {
		panic(err)
	}
	defer close(client, ctx, cancel)

	r := gin.Default()
	r.MaxMultipartMemory = 8 << 20 //8Mib
	r.GET("/", get)
	r.POST("/submit", submit)

	r.Run()
}
