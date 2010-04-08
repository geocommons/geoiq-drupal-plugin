if (Drupal.jsEnabled){
  $(document).ready(function() { 

      $('#geoiq-submit').click(function(){
        $('#geoiq-ajax-spinner').css('visibility', 'visible');
         var search = $('#geoiq-search').val();
         getResults(search);
           
      });

      $('#geoiq-submit-feed').click(function(){
         $('#geoiq-ajax-spinner').css('visibility', 'visible');
         var feed = $('#geoiq-feed-address').val();
         feed = feed.replace(/\//g, "|");
         insertFeed(feed);
         
      });
  });

 function embedMap(id){

   var code = '<style>#maker_map_MAPID {width: 100%; height: 400px;}</style><div class="geocommons_map" id="maker_map_MAPID"></div><br/><a class="geocommons_map_link" id="maker_map_MAPID_link" href="http://maker.geocommons.com/maps/MAPID">View full map</a> <script type="text/javascript" charset="utf-8" src="http://maker.geocommons.com/javascripts/embed.js"></script><script type="text/javascript" charset="utf-8">  Maker.maker_host="http://maker.geocommons.com";Maker.finder_host="http://finder.geocommons.com";Maker.core_host="http://core.geocommons.com"; Maker.load_map("maker_map_MAPID", "MAPID" );</script>' ;
    

   code = code.replace(/MAPID/g, id);
      
   $("#geoiq-map-code").val(code);
   $("#geoiq-map-code").css("visibility", "visible");
     
   var content = $('#edit-body').val();
   $('#edit-body').val(content + code);
         
 }

 function getResults(query){
    var serviceURL = createServiceURL('node', '/geocommons/api_search_js' , query);
    $.ajax({
        url: serviceURL,
        type: 'GET',
        success: showSearchResults,
        error: stopAjaxSpinnerWithError,
        dataType: 'json'
    });
 }

 function showSearchResults(data){
    if (data.status == true){
      $("#geoiq-results").html(data.data);
    }
    else{
      $("#geoiq-results").html(data.data);
      $("#geoiq-results").css('border-color', '#FF3333');
      $("#geoiq-results").css('color', '#FF3333');
    }
    $('#geoiq-ajax-spinner').css("visibility", 'hidden');
 }

 function createServiceURL(boundary, path, data){
  var result = "";
  var href = location.href;
  var pathRegex = new RegExp("^(.*)\/" + boundary + "/");
  var base = href.match(pathRegex);
  var result = base[1] + path;
  result += "/" + data;
  return result;
 }

 function stopAjaxSpinnerWithError(){
    $("#geoiq-results").html("<p>Grave error. Please contact the maintainer of the module.</p>");
    $("#geoiq-results").css('border-color', '#FF3333');
    $("#geoiq-results").css('color', '#FF3333');
    $('#geoiq-ajax-spinner').css("visibility", 'hidden');
 }

  function insertFeed(address){

    var serviceURL = createServiceURL('admin', '/geocommons/api_add_js', address);

    $.ajax({
        url: serviceURL,
        type: 'GET',
        success: showInsertFeedback,
        error: stopAjaxSpinnerWithError,
        dataType: 'json'
    });
   
 }

 function showInsertFeedback(data){
      $("#geoiq-feed-message").css('border-style', 'solid');
      $("#geoiq-feed-message").css('border-width', '2px');
      $("#geoiq-feed-message").css('border-color', '#2C8DC8');

      if (data.status == true){
        $("#geoiq-feed-message").css('border-color', '#006600');
      $("#geoiq-feed-message").css('color', '#006600');

      $("#geoiq-feed-message").html(data.data);
    }
    else{
      $("#geoiq-feed-message").css('border-color', '#FF3333');
      $("#geoiq-feed-message").css('color', '#FF3333');
                
      $("#geoiq-feed-message").html(data.data);
    }
            
    $('#geoiq-ajax-spinner').css("visibility", 'hidden');
 }
  
}
