const keywords = [
    'fn',
    'type',
    'int8',
    'string',
    'returns',
    'return'
]

function findKeywords(tokens, input, inputIndex) {
    for(const keyword of keywords) {
        if(
            input[inputIndex] === keyword[0] && 
            input.slice(inputIndex, inputIndex + keyword.length) === keyword 
        ) {
            tokens.push({
                value: keyword,
                type: 'keyword'
            })
        }
    }
    
    return tokens
}

const parens = [
    '(',
    ')',
    '{',
    '}'
]

function findParens(tokens, input, inputIndex) {
    for(const paren of parens) {
        if(
            input[inputIndex] === paren[0] && 
            input.slice(inputIndex, inputIndex + paren.length) === paren 
        ) {
            tokens.push({
                value: paren,
                type: 'paren'
            })
        }
    }

    return tokens
}

const identifiers = /[a-zA-Z][a-zA-Z0-9_]{0,30}/

function findIdentifiers(tokens, input, inputIndex) {
    let text = ''
    for(const c of input.slice(inputIndex)) {
        if(/[a-zA-Z0-9_]/.exec(c)) {
            text += c
        } else {
            break
        }
    }

    if(identifiers.exec(text)) {
        tokens.push({
            value: text,
            type: 'identifier'
        })
    }

    return tokens
}

module.exports = function(input) {
    if(typeof input !== 'string') {
        console.log("ERROR: input to tokenizer was not a string")
        return null
    } 
    
    let tokens = []
    let prevLength = 0
    for(let index = 0; index < input.length; index++) {
        ////////////////////////////////////
        // To track changes
        prevLength = tokens.length

        ////////////////////////////////////
        // Index is string...
        //index = parseInt(index)

        ////////////////////////////////////
        // Look for keywords
        tokens = findKeywords(tokens, input, index)
        if(prevLength !== tokens.length) {
            // Token found, move index past
            index += tokens[tokens.length - 1].value.length - 1
            continue
        }

        ////////////////////////////////////
        // Look for parenthesis
        tokens = findParens(tokens, input, index)
        if(prevLength !== tokens.length) {
            // Token found, move index past
            index += tokens[tokens.length - 1].value.length - 1
            continue
        }

        ////////////////////////////////////
        // Look for identifiers
        tokens = findIdentifiers(tokens, input, index)
        if(prevLength !== tokens.length) {
            // Token found, move index past
            index += tokens[tokens.length - 1].value.length - 1
            continue
        }
    }

    return tokens
}