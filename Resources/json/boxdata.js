function sortData(arrayToSort){
    return arrayToSort.sort(function(a,b){
        return a-b;
    })
}

function quartile(arr,q){
    //arr=sortData(arr);
    var pos=(arr.length+1)*q;
    var base=Math.floor(pos);
    var rest=pos-base;

    return ((base+1-pos)*arr[base]+rest*arr[base+1])
}

function boxData(boxData){
    for(var i=0;i<boxData.length;++i){
        var sunArray=sortData(boxData[i]);
        var Q1=quartile(sunArray,0.25);
        var Q2=quartile(sunArray,0.5);
        var Q3=quartile(sunArray,0.75);
        var min=sunArray[0];
        var max=sunArray[sunArray.length-1];
    }
}

