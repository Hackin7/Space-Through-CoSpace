var canvas = null;
var ctx = null;
var spritesheet = null;
var spritesheetLoaded = false;

// World Data
var world = [[]];
var worldWidth = 20;
var worldHeight = 16;

var tileWidth = 32;
var tileHeight = 32;


var pathStart = [worldWidth, worldHeight];
var pathEnd = [0,0];
var currentPath = [[0,0],[1,1],[2,2]];
 if (typeof console == "undefined") var console = { log: function(){}};
 
 function onload()
 { console.log('Page loaded.');
     canvas = document.getElementById('gameCanvas');
     canvas.width = worldWidth * tileWidth;
     canvas.height = worldHeight * tileHeight;
     canvas.addEventListener("click",canvasClick, false);
     if (!canvas) alert('Blah!');
    ctx = canvas.getContext("2d");
    if (!ctx) alert('Hmm!');
     spritesheet = new Image();
    spritesheet.src = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAKAAAAAgCAYAAACVf3P1AAAACXBIWXMAAAsTAAALEwEAmpwYAAAABGdBTUEAALGOfPtRkwAAACBjSFJNAAB6JQAAgIMAAPn/AACA6QAAdTAAAOpgAAA6mAAAF2+SX8VGAAAIN0lEQVR42mJMWaLzn4FEoCrxC86+/YINRQzER2aj68GmnhDgOx6EV/6T5Tqy7S9zvsnIMAoGDAAEEGPnHrX/6IkAFDm4EgZy4kNPhMSaQUgdTAyW8Oz1pMC0sAw7irq3T36C6YOXnqEkRlLsnx19eTQBDiAACCAWWImBHFnEJD7kkgYbICbykc1Btx+U+NATnqKhBpruG2AySEYRniAPAvWBEiGx9sNzYiQj3prg//L/jLQ0b72zN171gXu3kmQ/qebZiEv9/8fwn+E/UNdfIPEXyPsHpMEYKH/53RuS7CfWPIAA7JXhCoBACIPn9Crq/d83VncghEf0O0GQ4eafD2T1qmbgjf0xVyDOAK1glSfDN+oJ361lXaDKJ7/67f2/gCMadg+s7licaCRoBlN/zLsyI7Apkw63npn2TgHEQqhahEUivioNW7uL2CoQHbxcH4GS+NCrXWRw//wNDDGQelCJCC4NgWbxoVXNhACpJR2p5hAqGUkt6Ug1B1fJyM3KyvDn3z+GTY/uUcX+nU8fYjXHWETs/z8kPkAAsWBrvBPqfOBLiKRWwej2v8SS8LCVftgSH6q6GxhVMykJcaQBHmBJ9evfP5rbAyoF//7/C+cDBBALsaUeMYmP0o4HrPTD1eZDTnTIcjDxM5svgvUiV80gOZRSEZgQxQNXkFU6D2cAShgMDPRIgKhVMEAAseArydBLNPQSktjOC6HqnRgAS2S42oIweVAie/vkIrwURU+I9gxS4KqZAWnoZhQwMPz4+weI/9J+2AWc+hBJECCAmEjtscISDjmRh6wH21giPoDe4cCWOLG1F9ETLkzNaOJDBT+B1S8oEdIaMKF1aQACiAm5tMOVQEgZiiGlR4zRo75/H2V8j1gAS5wgbOKrj7NdiJ6AR6thBPj+5w/DdzokQHQAEEAsuEo4QpGDa/CZmMRHbFsRVHrhKvVwqYVVtbiqa1zup1bvl9zeMbV6v+T2jrc/eUAX+4+8fIZiD0AAMWFLIPgSB7ocKe05UmZXYKUgKEFh6/EiJzyYPHJ1S2zCHQUDCwACiAm5x0ssIGYYBlcbD1vvF109qARDb8+hJ0JsCZNQwsOXkEfBwACAAGIhp2ok1HNGb0sit/UIlbD4hmCQq2RSSzjkxAdqa4pb4lTqAMT5QCwAxI1ArADE8UjyF4C4EMpeD8QTgfgAlL8fSh+A6k3Ao5dYUADE/kD8AaoXRPdD3QWyewNUHcgufSTzDaB4wWBOgAABxIStQ0CNXiJyQiTGrCN95gyqiop4OxrklmIk6qkH4kQgdgTiB9AIdITKOSJFcAA0QcWj6XeEJg4HPHqJBf1IehOREt9CqFg8NJExQBOpANRuBihbnqapJ9T5PxhTAAACiAk94SGXWsTOjBDSi88sZPvR538pBeilJnLb8uHG3/i0wkrAB3jU+ENLIAMkMQFowlMgoJdYADJ7AlJpBhODlbgToe6A2XcQmjFoD5ATHgWJECCAmHAlKmJLQFxjgrg6K5QAUjoX+AauCQBQyfIQiOdDqzVsAFbSfIAmhgAk8Xyo2AMqRrcBtGQ2gNqJLcNshFbH8UOpDQgQQEy4SjRsJSOpHRRizSBQGmEkKljJhq1qRRbHVW2DqnqOr2b47F0ArfJwRWYANLHthyYKf6g4KNEFIslTK/EtQCr1GJDM9oeWeg7QBLoerRqmHVi9lxErm0QAEEAs+Hqx2PjI4qTM/xIDQAtLYQsI0KtO9KEWQu07CoZh9iOxG/FUv4FIpdx5NPmJ0FKpkcIgKYSWxLBSbyNUDJbQDkDlLkAzDKwzAmufJkATJwNSW5Q2iZBMABBAjLiW5GNLgPiqVGwJlFjwcpkhvAOCvBiB2GoZW2LEVfqBFyRAV1CDesObti4aXRE9gAAggJiwtf3IGRskpB5XhwVWDSJ3QPBNxcHk8LUH8SU+WnR2RgH5ACCAmHD1VPENNhMq4YiZH8Ymhi9hQFa5/ERZ4ULFoZdRMEAAIICY8HUkiF0LiCyPa6YDVzUO6gzgG/9DBrCqGV/iQl+aRUypCm6LRDL+J7RamRoAlz2glcqE9nFQA+CyR19I5L8uENPafnR7AAKIhZg1faQuTCCmDYisBrndhy2hYBPDNcwCEsemHt18kJ2w1TejgAG8V+P///90twcggFiQOxCkdh4IdThw7R9GZr9ESmTY5oBJqWrREx6ubZywHvcoQE0Y/wbAHoAAYsG3rIrYxIUvYRKzegaUGLC1/0hdF4gr8WEzB1T6sYueGE15UIC+V4Ne9gAEEAs1Eh+uZfbEVN3iUecZbi+DClzC3ylBTkj4SjdCiQ9W+gm4so+mPHjCIG/7JaX2AAQQyathCPVwYb1pUk5XQE6EyOOB6AkG21ANriob26kJmKXfaAKEAdBe4L//mWhuD/qeEIAAYsHXeSB2TR+lnRZYIgSNCd6+j0gkyAkSX1WNXvXiSnwwM39wn2IQx1H64eoJU/tkBHy9VGzi1D4ZAR1wMbOCaUsxyf/UOBkhSEHlPzsTEwMHMwvYrC9//jB8/f0bY08IQACxkNrGo8a0G67SUd4fFAiQhMjP9Q+aaJD0ETFcg574kHu6oIQHAjCzRwECcLKwgA7SACaPvwx/gAnmDzCIfv8DHa4BzExk9I4hpyEwMbAwARPcPyac1TtAAOGdikOuUolJfLgSFq5pPWLamXtmMsITzM/XFvCEiH56AmyKDX1oBZToQPo/fkNULy7p/+H2jx5ONLAAIIBwno6Fq0rGt3EJ37Fo6ImZmKofmzgoQYIGr3EBUNsOObHBEq9pLCNW+0ePZxtYABBgAEdytom0/RTgAAAAAElFTkSuQmCC';
  spritesheet.onload = loaded;
}
function loaded(){
    console.log('Spritesheet loaded.');
    spritesheetLoaded = true;
    createWorld();
}
function createWorld(){
    console.log('Creating world...');
    
    //Emptiness
    for (var x=0; x< worldWidth; x++){
        world[x] = [];
        for (var y=0; y<worldHeight; y++){
            if (Math.random()>0.75)world[x][y] = 1;
            else world[x][y] = 0;
        }
    }
    
    //Calculate initial possible path
    
    currentPath = [];
    while (currentPath.length == 0){
        pathStart = [Math.floor(Math.random()*worldWidth),Math.floor(Math.random()*worldHeight)];
        pathEnd = [Math.floor(Math.random()*worldWidth),Math.floor(Math.random()*worldHeight)];
        if (world[pathStart[0]][pathStart[1]] == 0)
        currentPath = findPath(world,pathStart,pathEnd);
    }
    redraw();
}

function redraw(){
    if (! spritesheetLoaded) return;
    console.log('redrawing...');
    var spriteNum = 0;
    
    //ctx.fillStyle = '#000000';
    ctx.fillRect(0,0,canvas.width, canvas.height);
    for (var x=0; x<worldWidth;x++){
        for (var y=0; y<worldHeight; y++){
            //Which type
            switch(world[x][y]){
                case 1:
                    spriteNum = 1;
                    break;
                default:
                    spriteNum = 0;
                    break;
            }
            //Draw
            ctx.drawImage(spritesheet,spriteNum*tileWidth, 0, tileWidth, tileHeight, x*tileWidth, y*tileHeight, tileWidth, tileHeight);
        }
    }
    //draw path
    console.log('Current path length: '+currentPath.length);
    for (rp=0; rp < currentPath.length; rp++){
        if (rp==0)spriteNum = 2; //Start
        else if (rp == currentPath.length-1) spriteNum = 3;//End
        else spriteNum=4;// Path Node
        ctx.drawImage(spritesheet,spriteNum*tileWidth, 0, tileWidth, tileHeight, currentPath[rp][0]*tileWidth, currentPath[rp][1]*tileHeight, tileWidth, tileHeight);
    }
}

// handle click events on the canvas
function canvasClick(e)
{
    var x;
    var y;

    // grab html page coords
    if (e.pageX != undefined && e.pageY != undefined)
    {
        x = e.pageX;
        y = e.pageY;
    }
    else
    {
        x = e.clientX + document.body.scrollLeft +
        document.documentElement.scrollLeft;
        y = e.clientY + document.body.scrollTop +
        document.documentElement.scrollTop;
    }

    // make them relative to the canvas only
    x -= canvas.offsetLeft;
    y -= canvas.offsetTop;

    // return tile x,y that we clicked
    var cell =
    [
    Math.floor(x/tileWidth),
    Math.floor(y/tileHeight)
    ];

    // now we know while tile we clicked
    console.log('we clicked tile '+cell[0]+','+cell[1]);

    pathStart = pathEnd;
    if (world[pathStart[0]][pathStart[1]] == 0)pathEnd = cell;

    // calculate path
    currentPath = findPath(world,pathStart,pathEnd);
    redraw();
}

function findPath(world, pathStart, pathEnd){
    //Convenient usage
    var abs = Math.abs;
    var max = Math.max;
    var pow = Math.pow;
    var sqrt = Math.sqrt;
    
    var worldWidth = world[0].length;
    var worldHeight = world.length;
    var worldSize = worldWidth * worldHeight;
    
    var distanceFunction = manhattenDistance;
    var findNeighbours = function(){};
    
    function manhattenDistance(Point, Goal){
        //linear movement - no diagonals - just cardinal directions (NSEW)
        return abs(Point.x - Goal.x) + abs(Point.y - Goal.y);
    }
    
    function Neighbours(x,y){
        var North = y-1, 
        South = y+1, 
        East = x+1, 
        West = x-1;
        var NorthConnected = North>-1 && canWalkhere(x,North),
        SouthConnected = South<worldHeight && canWalkhere(x,South),
        EastConnected = East<worldWidth && canWalkhere(East,y),
        WestConnected = West>-1 && canWalkhere(West, y),
        
        neighbours = [];
        if (NorthConnected){
            neighbours.push({x:x,y:North})}
        if (SouthConnected){
            neighbours.push({x:x,y:South})}
        if (EastConnected){
            neighbours.push({x:East,y:y})}
        if (WestConnected){
            neighbours.push({x:West,y:y})}
        findNeighbours(NorthConnected, SouthConnected, EastConnected, WestConnected, North, South, East, West, neighbours);
        return neighbours;
    }
    
    function canWalkhere(x,y){
        return ((world[x] != null) &&
                (world[x][y] != null) &&
                (world[x][y] == 0)); //Walkable Tile Value 
    }
    // Used in function
    // CalculatePath
    function Node(Parent, Point){
        var newNode = {
            //pointer to another Node object
            Parent:Parent,
            //array index of this Node in the world linear array
            value:Point.x + (Point.y * worldWidth),
            //Coordinates
            x:Point.x,
            y:Point.y,
            //Cost from start to node
            f:0,
            //Cost from Node to Goal
            g:0
        };
        return newNode;
    }
    function calculatePath(){
        // create Nodes from Start and End x, y coordintes
        var myPathStart = Node(null, {x:pathStart[0], y:pathStart[1]});
        var myPathEnd = Node(null, {x:pathEnd[0], y:pathEnd[1]});
        var AStar = new Array(worldSize);
        var Open = [myPathStart];
        var Closed = [];
        var result = [];
        var myNeighbours, myNode, myPath;
        
        var length, max, min, i, j;
        //Iterate through openlist until no nodes left
        while (length = Open.length){
            max = worldSize;
            min = -1;
            for (i=0; i<length;i++){ 
                if (Open[i].f < max){ // If there is a smaller cost from start
                    max = Open[i].f;
                    min = i;
                }
            }
            
            //grab next node and remove it from Open array
            myNode = Open.splice(min, 1)[0];
            //Is it destination node?
            if (myNode.value === myPathEnd.value){
                myPath = Closed[Closed.push(myNode)-1];
                
                do{result.push([myPath.x, myPath.y])}
                while (myPath = myPath.Parent);
                AStar = Closed = Open = [];//Clear all working arrays
                result.reverse(); // Order from start to end
            }
            else{ //not destination
                myNeighbours = Neighbours(myNode.x, myNode.y);
                for (i=0, j=myNeighbours.length;i<j;i++){
                    myPath = Node(myNode, myNeighbours[i]);
                    if (!AStar[myPath.value]){ //If not visited before
                        //estimated cost of this particular route so far
                        myPath.g = myNode.g + distanceFunction(myNeighbours[i], myNode);
                        //estimated cost of this particular route so far
                        myPath.f = myPath.g + distanceFunction(myNeighbours[i], myPathEnd);
                        Open.push(myPath);
                        //mark this node in the world graph as visited
                        AStar[myPath.value] = true;
                        
                    }
                    
                }
                //remember this route has having no more untested options
                Closed.push(myNode);
            }
        }
        return result;
        /////////////////////CONTINUE////////////////////////////////
    }// actually calculate the a-star path!
    // this returns an array of coordinates
    // that is empty if no path is possible
    return calculatePath();
}
onload();
//alert("ready");
