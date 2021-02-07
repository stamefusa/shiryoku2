export default function (req, res) {
    const url = require('url')
    const SerialPort = require('serialport');

    const port = new SerialPort('/dev/ttyS3', { // Ubuntu on Windows10
        baudRate: 9600
    });

    // シリアルポートがオープンされたときの処理
    port.on('open', function () {
        // シリアルポートへの送信
        // URLのvalueパラメータを取得し送信
        write(port, url.parse(req.url, true).query['value']).then((data) => {
            // APIのレスポンス返却
            res.writeHead(200, { 'Content-Type': 'text/plain' })
            res.write(data)
            res.end()
        })
        // 状態に関わらずシリアルポートをクローズしておく
        .finally((data) => {
            port.close()
        })
    });
}

function write(port, src) {
    // Serialport.write()は非同期処理なので、Promiseでくるんで処理
    return new Promise((resolve, reject) => {
        port.write(src)
        port.once('data', (data) => {
            resolve(data.toString())
        })
        port.once('error', (err) => {
            reject(err)
        })
    })
}