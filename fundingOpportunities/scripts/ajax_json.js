<script type ="text/javascript">


function ajax_get_json(){

// create our XMLhttpRequest object

var hr = new XMLHttpRequest();

hr.open("GET","data/sources/funding_opportunities.json",true);

// set the header of the request

 hr.setRequestHeader("content-type","application/json");
//access the onreadystatechange event for the XMLHttpRequest object

hr.onreadysatechange=function(){
if(hr.readyState == 4 && hr.status ==200){
var data == JSON.parse(hr.responseText);
$mydata= data;
document.write data;

}



}




}
</script>