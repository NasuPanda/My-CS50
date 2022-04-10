## `fopen`

- NULLが返ってきていないかチェックすること。

```c
FILE* ptr = fopen(<filename>, <operation>);

// 例
FILE* ptr = fopen("file1.txt", "r");
```

## `fclose`

ファイルポインターを渡すと、ポイントされているファイルを閉じる。

```c
fclose(<file pointer>)
```

## `fgetc`

- ファイルから1文字読み込み、その文字を返す。
- 位置指定子を1進める

```c
char ch = fgetc(<file pointer>);
```

## `fread`

`<buffer>`に`<file pointer>`から読み込んだ値を書き込む。
実行する度に「ファイル位置指示子」が読み込んだデータバイト分だけ進む。

`<qty>` : 読み込むデータ数
`<size>` : sizeバイトのデータを読み込む

```c
fread(<buffer>, <size>, <qty>, <file pointer>);
```

```c
uint8_t header[HEADER_SIZE];

// 上と下は等価
fread(header, sizeof(uint8_t), HEADER_SIZE, input);
fread(header, HEADER_SIZE, 1, input);
```