### 3dtiles 使用说明

![](https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/img/20190620210305.png)

[TOC]



#### 声明:

[fanvanzh/3dtiles]: https://github.com/fanvanzh/3dtiles	"fork fanvanzh/3dtiles"

 下载master  分支  时间于:2019-04 -22   将其作为基础版本，进行修改和相关的需求的更改和优化

![](https://raw.githubusercontent.com/touwoyimuli/FigureBed/master/img/20190620205610.png  )





------



### **本版本`【3dtiles  v4.0】`,**

#### 修改时间:

2019_06_20

#### 说明:

在上一个`【3dtiles  v3.2】`版本里面, 做了内容的修改，修复一个可能导致程序运行的bug，且新增日志和进度功能，均已文件形式记录。

#### 如何使用：

1. 打开"cmd",运行

2. 通过cd 相关的命令，进入到"3dtile.exe"一级的目录下

```html
cd D:\programming\DataTest\3dtiles\target\release
```

3. 运行命令

示范一：

```html
 3dtile.exe -f osgb -i D:\Osgb\Data -x D:\xmlPath\metadata.xml -o D:\DataOsgb_23dtiles
```

示范二：

```html
3dtile.exe -f osgb -i D:\Osgb\Data -x D:\xmlPath\metadata.xml -o D:\DataOsgb_23dtiles –p D:\LOG\Tile_TXT -d D:\Json\Count\test.json
```

#### 参数说明：

**<font color=#D0087E size=4 face="幼圆">-f：输入类型转换参数</font>**  osgb, 	shape, 	gltf

**<font color=#D0087E size=4 face="幼圆">-i：输入文件夹参数。</font>**  要精确到`.\Data`一级目录

`D:\Osgb_Data`为`Tile_xxx_xxx`的数据输入目录 

说明：[如果有root目录，就会现在root里面寻找Tile_xxx_xxx，若是没有root文件夹，则会自动判断，找root的同级的Tile_xxx_xxx]

**<font color=#D0087E size=4 face="幼圆">-x：输入文件参数。</font>** 	输入路径**带**具体文件名称（一定要是.xml文件）。

`D:\xmlPath\metadata.xml` 即为`metadata.xml`的输入目录   （`metadata.xml` 也可以是任何名称`xxx.xml`）

**<font color=#D0087E size=4 face="幼圆">-o：输出文件夹参数。</font>** 	选择任意一个已存在的空文件夹

`D:\DataOsgb_23dtiles` 为输出目录

**<font color=#D0087E size=4 face="幼圆">-p：调试参数。(可选参数)</font>** 	后面若输入`-p  “”`, 或者不输入该参数。则运行时候，不会出创建日志，记录当前具体`Tile_xx.osgb`的运行到哪一个地方了，若是该Tile_xx转换成功，则随即删除该`Tile_xx_Log.txt`日志；

​		若是输入 <font color=#70AD47 size=3 face="幼圆">-p  "任意路径**不带**具体文件名(可已存在或不存在)" </font> 则运行时候，会出现自动跟踪和创建日志

**<font color=#D0087E size=4 face="幼圆">-d：调试参数。(可选参数)</font>** 后面若输入`-d  “”`, 或者不输入该参数。则运行时候，不会出现创日志文件，保存任务进度等信息；

​		若是输入 <font color=#70AD47 size=3 face="幼圆">-d "任意路径**带**具体文件名(可已存在或不存在)"</font>则运行时候，会出现自动跟踪和创建日志



**说明:**	若是选用-p、-d参数，可以在程序运行或结束后时候，到对应的文件夹下查看日志文件和进度条，



------



### **本版本`【3dtiles  v3.2】`,**

#### 修改时间:

2019_05_20

#### 说明:

在上一个`【3dtiles  v3.0】`版本里面 做了内容的修改

#### **功能：**

**1.metadata.xml（`metadata.xml`可以是其他名称`abc.xml`）文件的路径(包含是到..\metadata.xml)可以是任意的路径，直接传入`xxx.xml`文件，无需放在和Data的同级目录**

2.直接传入`Tile_xxx_xxx`的上一级Data路径，和metadata.xml的上一级路径，分别是独立的

**3.当遇到没有数据的`Tile_xxx_xxx`时候，会自动跳过，执行下一个有数据的`Tile_xxx_xxx`。不会像上一个版本一样，整个程序终止**



#### 如何使用：

**注意： **

1.在命令行里面多了一个参数 `-x E:\DataXml`， 这是metadata.xml的路径，且是必须参数，不可或缺



2.将直接使用Tile_xxx_xxx 的一级目录，和metadata.xml一级目录，且可以单独独立分开

比如:`D:\Osgb_Data` 和 `D:xmlPath` ，其目录结构如下



Osgb_Data

> root
>
> ```
> 	>Tile_-xxx_+xxx
> 	>
> 	>...
> ```
>
> Tile_-001_+001
>
> Tile_-001_+002
>
> Tile_-001_+003
>
> ...

其中root文件夹可有可无



xmlPath

```
	>metadata.xml
```



**举例:**

1. 打开"cmd",运行
2. 通过cd 相关的命令，进入到"3dtile.exe"一级的目录下
3. 运行命令”`3dtile.exe -f osgb -i D:\Osgb_Data -x D:xmlPath\abc.xml -o D:\DataOsgb_23dtiles`“

```rust
cd D:\programming\DataTest\3dtiles\target\release

3dtile.exe -f osgb -i D:\Osgb_Data -x D:xmlPath\abc.xml -o D:\DataOsgb_23dtiles
```

其中最后一个命令:

`D:\Osgb_Data`为Tile_xxx_xxx的数据输入目录   

 [如果有root目录，就会现在root里面寻找Tile_xxx_xxx，若是没有root文件夹，则会自动判断，找root的同级的Tile_xxx_xxx]

**`D:xmlPath\abc.xml` 为metadata.xml的输入目录**  **(这里改了)**

`D:\DataOsgb_23dtiles`为输出目录



------

### **本版本`【3dtiles  v3.0】`,**

#### 修改时间:

2019_05_08

#### 说明:

在上一个`【3dtiles  v2.0】`版本里面 做了内容的修改

#### **功能：**

1.metadata.xml文件的路径可以是任意的路径，无需放在和Data的同级目录

2.直接传入Tile_xxx_xxx的上一级Data路径，和metadata.xml的上一级路径，分别是独立的



#### 如何使用：

**注意： **

1.在命令行里面多了一个参数 `-x E:\DataXml`， 这是metadata.xml的上路径，且是必须参数，不可或缺



2.将直接使用Tile_xxx_xxx 的一级目录，和metadata.xml一级目录，且可以单独独立分开

比如:`D:\Osgb_Data` 和 `D:xmlPath` ，其目录结构如下



Osgb_Data

> root
>
> 		>Tile_-xxx_+xxx
> 		>
> 		>...
>
> Tile_-001_+001
>
> Tile_-001_+002
>
> Tile_-001_+003
>
> ...

其中root文件夹可有可无



xmlPath

		>metadata.xml



**举例:**

1. 打开"cmd",运行
2. 通过cd 相关的命令，进入到"3dtile.exe"一级的目录下
3. 运行命令”`3dtile.exe -f osgb -i D:\Osgb_Data -x D:xmlPath -o D:\DataOsgb_23dtiles`“

```rust
cd D:\programming\DataTest\3dtiles\target\release

3dtile.exe -f osgb -i D:\Osgb_Data -x D:xmlPath -o D:\DataOsgb_23dtiles
```

其中最后一个命令:

`D:\Osgb_Data`为Tile_xxx_xxx的数据输入目录   

 [如果有root目录，就会现在root里面寻找Tile_xxx_xxx，若是没有root文件夹，则会自动判断，找root的同级的Tile_xxx_xxx]

`D:xmlPath` 为metadata.xml的输入目录

`D:\DataOsgb_23dtiles`为输出目录



------

### **本版本`【3dtiles  v2.0  版本bug解决，附带思路】`**

#### **修改时间:**

2019_04_28

#### **说明:**

仅针对于osgb转换3dtiles格式的修改

#### 解决的问题：

直接转换，不会如下的错误出现 ，可以直接在CesiumLab发布，正常显示浏览

```js
RuntimeError: Unsupported glTF Extension: KHR_technique_webgl
```

#### 解决思路：

> 我发现原因是KHR_technique_webgl扩展新版Cesium已经不支持的缘故，需要升级一下gltf数据，使用KHR_techniques_webgl扩展即可(注意多了一个s)。
> 当然如果直接修改3dtiles数据，比较劳心费神。这里提供一个简单的方法，只需要在Cesium.js加载以后，运行以下代码即可正常显示3dtiles数据了。附上原文:([解决Cesium1.50对gltf2.0/3dtiles数据读取的问题](https://www.jianshu.com/p/e0e0a62c5726))

查阅资料可知：*.osgb的二进制数据前面 + 一段json的说明 = *.b3dm

由上面的原因可知，外加本工具是在github上面开源的，可以直接修改源码，在3dtiles工具上面，直接修改这一段json的格式即可以；

修改规则参考如下代码：

```js
var fixGltf = function(gltf) {
    if (!gltf.extensionsUsed) {
        return;
    }

    var v = gltf.extensionsUsed.indexOf('KHR_technique_webgl');
    var t = gltf.extensionsRequired.indexOf('KHR_technique_webgl');
    // 中招了。。
    if (v !== -1) {
        gltf.extensionsRequired.splice(t, 1, 'KHR_techniques_webgl');
        gltf.extensionsUsed.splice(v, 1, 'KHR_techniques_webgl');
        gltf.extensions = gltf.extensions || {};
        gltf.extensions['KHR_techniques_webgl'] = {};
        gltf.extensions['KHR_techniques_webgl'].programs = gltf.programs;
        gltf.extensions['KHR_techniques_webgl'].shaders = gltf.shaders;
        gltf.extensions['KHR_techniques_webgl'].techniques = gltf.techniques;
        var techniques = gltf.extensions['KHR_techniques_webgl'].techniques;

        gltf.materials.forEach(function (mat, index) {
            gltf.materials[index].extensions['KHR_technique_webgl'].values = gltf.materials[index].values;
            gltf.materials[index].extensions['KHR_techniques_webgl'] = gltf.materials[index].extensions['KHR_technique_webgl'];

            var vtxfMaterialExtension = gltf.materials[index].extensions['KHR_techniques_webgl'];

            for (var value in vtxfMaterialExtension.values) {
                var us = techniques[vtxfMaterialExtension.technique].uniforms;
                for (var key in us) {
                    if (us[key] === value) {
                        vtxfMaterialExtension.values[key] = vtxfMaterialExtension.values[value];
                        delete vtxfMaterialExtension.values[value];
                        break;
                    }
                }
            };
        });

        techniques.forEach(function (t) {
            for (var attribute in t.attributes) {
                var name = t.attributes[attribute];
                t.attributes[attribute] = t.parameters[name];
            };

            for (var uniform in t.uniforms) {
                var name = t.uniforms[uniform];
                t.uniforms[uniform] = t.parameters[name];
            };
        });
    }
}

Object.defineProperties(Cesium.Model.prototype, {
    _cachedGltf: {
        set: function (value) {
            this._vtxf_cachedGltf = value;
            if (this._vtxf_cachedGltf && this._vtxf_cachedGltf._gltf) {
                fixGltf(this._vtxf_cachedGltf._gltf);
            }
        },
        get: function () {
            return this._vtxf_cachedGltf;
        }
    }
});
```

不过我们这里，是使用C++来翻译这段代码，为了简便，使用QtJson的模块来对这一段json进行规则重组。

#### 编译说明：

将源码编译成可执行程序"3dtile.exe"的操作步骤如下：

1、安装 vs 2015（update 3）或 vc 2015 c++ build tools（update 3）。

2、设置 rustup 的代理 (环境变量）：(for chinese user only)

```
set RUSTUP_DIST_SERVER=http://mirrors.ustc.edu.cn/rust-static
set RUSTUP_UPDATE_ROOT=http://mirrors.ustc.edu.cn/rust-static/rustup
```

3、下载 rustup-init.exe 自动安装工具并按默认执行， 链接： [rustup_init.exe](https://static.rust-lang.org/rustup/dist/i686-pc-windows-gnu/rustup-init.exe)

4、配置依赖源的代理：创建文件 C:/Users/<用户名>/.cargo/config (没有后缀）, 内容如下。

```c
[registry]
index = "https://mirrors.ustc.edu.cn/crates.io-index/"
[source.crates-io]
registry = "https://github.com/rust-lang/crates.io-index"
replace-with = 'ustc'
[source.ustc]
registry = "https://mirrors.ustc.edu.cn/crates.io-index/"
```

5、使用 git clone 下载源码（部分用户反馈http下载导致无法编译）

```c
git clone https://github.com/fanvanzh/3dtiles.git
```





==**配置所需要额qt依赖**==，版本为qt 5.9.7 MSVC 2015版本(因为的修改使用到了qt的模块库)

将`msvc2015_64`文件夹，放到`C:\Qt\Qt5.9.7\5.9.7\`下面即可.



命令行进入 3dtile 目录，执行命令：

```c
cargo build --release
```

6、编译好的结果在 3dtile/target/release 目录

7、本工程的预编译lib和dll均为64位平台，暂不支持在32位平台。

#### 如何使用：

1. 打开"cmd",运行
2. 通过cd 相关的命令，进入到"3dtile.exe"一级的目录下
3. 运行命令”`3dtile.exe -f osgb -i D:\DataTest -o D:\Data23dtiles`“

```c
cd D:\programming\DataTest\3dtiles\target\release

3dtile.exe -f osgb -i D:\programming\DataTest\DataOsgb -o D:\programming\DataTest\DataOsgb_23dtiles
```

其中最后一个命令:`D:\programming\DataTest\DataOsgb`为输入目录

`D:\programming\DataTest\DataOsgb_23dtiles`为输出目录

#### 格式说明：

输入目录：osgb格式数据,根目录下必须要有`Data`文件夹，和`metadata.xml`文件，缺一不可，且名称不可改变

- 常规osgb的目录结构：

> DataOsgb
>
> > Data
> >
> > > Tile_-001_+001
> > >
> > > Tile_-001_+002
> > >
> > > Tile_-001_+003
> > >
> > > ...
> >
> > metadata.xml



- 改进版osgb的目录结构：osgb格式数据,根目录下必须要有`Data`文件夹，和`metadata.xml`文件，缺一不可，且名称不可改变。且`Data`目录下，还有一个`root`文件夹，且`root（合并根节点而自动产生的）`也不可改变

> DataOsgb
>
> > Data
> >
> > > root
> >
> > > Tile_-001_+001
> > >
> > > Tile_-001_+002
> > >
> > > Tile_-001_+003
> > >
> > > ...
> >
> > metadata.xml



以上的两种文件夹结构方式，该项目可智能识别属于哪一种

#### 效果演示：

当用CesiumLab发布转换之后的3dtiles的数据，可以直接成功的显示刷新



------

### 本版本`【3dtiles  v1.0 原版未修改，有bug不可使用】` 

#### 修改时间：

2019_04_22

即 “fork fanvanzh/3dtiles” 的基础版本，未做任何修改