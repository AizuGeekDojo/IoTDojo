package main

import (
	"fmt"
	"net/http"

	"github.com/gin-gonic/gin"
)

func main() {
	data := make([]string, 1, 1024)
	data[0] = "test"
	engine := gin.Default()
	engine.LoadHTMLGlob("src/*")
	engine.GET("/", func(c *gin.Context) {
		c.HTML(http.StatusOK, "index.html", gin.H{})
	})
	engine.GET("/getData", func(c *gin.Context) {
		str := ""
		for _, s := range data {
			str += s + "\r\n"
		}
		c.String(http.StatusOK, str)
	})
	engine.POST("/postData", func(c *gin.Context) {
		type Json struct {
			Msg string `json:"msg"`
		}
		var json Json
		c.BindJSON(&json)
		fmt.Println(json.Msg)
		data = append(data, json.Msg)
		c.String(http.StatusOK, "OK")
	})
	engine.Run(":80")
}
