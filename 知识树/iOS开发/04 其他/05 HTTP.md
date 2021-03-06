## HTTP

### 1.0 - 1.1 - 2.0

#### HTTP1.0 ~ HTTP1.1 的区别

* 缓存处理
	* eTag
* 带宽优化及网络连接的使用
	* 请求头中有range的概念，可以断点续传
* 错误通知的管理
	* 新增错误状态的响应码
* Host头处理
	* 处理同一个IP地址下多个虚拟主机的情况
* 长连接
	* 支持长连接、和流水线(pipelining),可以在一个TCP连接上传送多个HTTP请求和响应，减少建立和关闭连接的消耗和延迟
		* pipelining，下一个请求需要等待上一个请求的返回，遇到网络延时会直接堵塞

#### SPDY: HTTP1.x的优化

* 降低延迟
	* 通过多路复用共享一个tcp连接
* 请求优先级
* header压缩
* 基于HTTPs的加密协议传输
* 服务端推送

#### HTTP2.0 ~ SPDY 的区别

2.0可以说是SPDY的升级版，但是依然存在少许区别

* 2.0依然支持明文的HTTP传输，SPDY强制HTTPS
* 消息头的压缩算法有不同

#### HTTP2.0 ~ HTTP1.x 的区别

* 采用二进制格式，HTTP1.x的解析是基于文本的
* 多路复用
* header压缩
* 服务端推送

### 多路复用

主要说明2.0中的多路复用和1.x中的长连接复用有什么区别

![](https://tva1.sinaimg.cn/large/0082zybpgy1gc4460b3s0j30kz0kp75s.jpg)

### 缓存机制

分为强缓存和协商缓存，各缓存头存在优先级，强缓存覆盖协商缓存；

#### 强缓存

只要请求了一次，在有效时间内都不会再请求服务器，会直接从浏览器本地缓存中获取资源；

* cache_control: max-age=time
	* 多久之后会过期
	* http1.1
* expire: date
	* 过期日期
	* http1.0

* cache_control优先级大于expire

#### 协商缓存

无论是否变化，是否过期都会发起请求，如果内容没有过期会直接返回 304；

* Etag: xxxx
	* 服务端返回的MD5值，记录当前版本
* If-None-Match: xxxx
	* 请求携带的字段，和Etag相同则返回304

* Last-Modified: date
	* 服务端字段，最后修改日期
* If-Modified-Since: date
	* 请求携带字段，相同返回304

* Etag优先级大于Last-Modified

### HTTPS 中的 TLS/SSL

![](https://tva1.sinaimg.cn/large/0082zybpgy1gc44pymwbxj30h30dhgnb.jpg)

* 0.建立TCP连接
* 1.客户端发起 client_hello
	* 发送版本信息，加密套件候选列表，压缩算法候选列表，`随机数A`，扩展字段等
* 2.服务端响应 server_hello
	* 返回协商使用的协议版本，加密套件，压缩算法，`随机数B`，`服务端配置对应的证书`
* 3.客户端证书校验
	* 证书链可信性
	* 证书是否被吊销
	* 证书是否在有效期
	* 证书域名是否和当前访问域名匹配
* 4.客户端再生成`随机数 pre-master`，并用`证书`的公钥加密，发送给服务器;
* 5.客户端通过三个随机数计算出`协商密钥 enc_key`，发送信令通知服务端后续的通信都采用加密通信;
* 6.客户端将之前所有通信参数的hash值与其他相关信息生成数据，用协商密钥加密后发送给服务器;
* 7.服务端用私钥解密得到`随机数 per-master`，计算得到`协商密钥 enc_key`;
* 8.服务端解密6的消息，验证数据和密钥的正确性，验证通过后发送信息通知客户端后续的通信都采用加密通信;
* 9.服务端也将之前所有的通信参数生成数据，用协商密钥加密发送给客户端;
* 10.客户端收到加密信息，解密后验证服务器数据和密钥的正确性，握手完成;

#### 会话标识 session ID

如果曾经建立了连接，那么握手成功后会返回sessionId，并保存相关参数在服务器中；

再次建连时，检索sessionId有命中，那么直接从信令之后的步骤执行；
