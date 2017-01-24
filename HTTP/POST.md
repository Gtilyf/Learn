# POST

POST提交的数据是放在消息主体中（entity_body）的，数据的编码方式由头部 (request header) 的`Content-Type` 字段指定，服务器端一般根据该字段选择采用对应的格式解析请求数据。

[四种常见的 POST 提交数据方式](https://imququ.com/post/four-ways-to-post-data-in-http.html)

#### application/json

```http
POST http://www.example.com HTTP/1.1 
Content-Type: application/json;charset=utf-8

{"title":"test","sub":[1,2,3]}
```

提交复杂的结构化数据，适用于RESTful接口，Google 的 [AngularJS](http://angularjs.org/) 中的 Ajax 功能，默认就是提交 JSON 字符串。



#### application/x-www-form-urlencoded

```http
POST http://www.example.com HTTP/1.1
Content-Type: application/x-www-form-urlencoded;charset=utf-8

title=test&sub%5B%5D=1&sub%5B%5D=2&sub%5B%5D=3
```

浏览器的原生<form>表单，如果不设置 `enctype` 属性便是采用的这种方式提交数据。



#### multipart/form-data

```http
POST http://www.example.com HTTP/1.1
Content-Type:multipart/form-data; boundary=----WebKitFormBoundaryrGKCBY7qhFd3TrwA

------WebKitFormBoundaryrGKCBY7qhFd3TrwA
Content-Disposition: form-data; name="text"

title
------WebKitFormBoundaryrGKCBY7qhFd3TrwA
Content-Disposition: form-data; name="file"; filename="chrome.png"
Content-Type: image/png

PNG ... content of chrome.png ...
------WebKitFormBoundaryrGKCBY7qhFd3TrwA--
```

设置<form>表单的 `enctype = multipat/form-data`， ，消息主体中由 `boundary` 分割不同的字段，该编码方式一般用于上传文件。



#### text/xml

```http
POST http://www.example.com HTTP/1.1 
Content-Type: text/xml

<?xml version="1.0"?>
<methodCall>
    <methodName>examples.getStateName</methodName>
    <params>
        <param>
            <value><i4>41</i4></value>
        </param>
    </params>
</methodCall>
```

XML-RPC协议。