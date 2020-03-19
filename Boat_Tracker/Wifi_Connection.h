// Request data from the server
int DoRequestFor(String url, bool getOrPost, String content = "") {
  SetLedsColor(0,0,255);
    
  HTTPClient http;
  http.begin(url); 
  http.addHeader("Content-Type", "text/plain");
  int httpCode = getOrPost ? http.GET() : http.POST(content);  
  Serial.println(httpCode);

  if(httpCode > 0) {
    deserializeJson(json, http.getString());

     // Light green when it went correct, else blink red
     if(httpCode >= 200 && httpCode < 299){
        SetLedsColor(0,255,0);
        PlaySequence(succesRequest);
     }
     else
        BlinkLightTimes(200, 255, 0, 0, 3);
  }
  else 
    BlinkLightTimes(200, 255, 0, 0, 3);

  http.end();

  return httpCode;
}
