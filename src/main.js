const fs = require('fs')
const tokenizer = require('./tokenizer')

const file = fs.readFileSync("scripts/test.deq").toString()

const tokens = tokenizer(file)

for(const token of tokens) {
    console.log('Token:', token)
}

console.log("Done!")