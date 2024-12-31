struct HttpRequest {
  String method;     // GET, POST, etc.
  String path;       // URL path, e.g., "/toggle_switch"
  String body;       // Request body (for POST)
  String headers;    // Request headers
  size_t length;     // Length of the request
};

HttpRequest parseRequest(String request) {
  HttpRequest parsedRequest;

  // Extract the method (GET, POST, etc.)
  int methodEnd = request.indexOf(' ');
  if (methodEnd != -1) {
    parsedRequest.method = request.substring(0, methodEnd);
  }

  // Extract the path (URL path)
  int pathStart = methodEnd + 1;
  int pathEnd = request.indexOf(' ', pathStart);
  if (pathEnd != -1) {
    parsedRequest.path = request.substring(pathStart, pathEnd);
  }

  // Extract the headers and body (for POST requests)
  int headerEnd = request.indexOf("\r\n\r\n");
  if (headerEnd != -1) {
    parsedRequest.headers = request.substring(0, headerEnd);  // Headers
    parsedRequest.body = request.substring(headerEnd + 4);  // Body
  }

  // Get the length of the request (for further processing or debugging)
  parsedRequest.length = request.length();

  return parsedRequest;
}

void printParsedRequest(HttpRequest parsedRequest) {
  Serial.println("Request Method: " + parsedRequest.method);
  Serial.println("Request Path: " + parsedRequest.path);
  Serial.println("Request Headers: " + parsedRequest.headers);
  Serial.println("Request Body: " + parsedRequest.body);
  Serial.println("Request Length: " + String(parsedRequest.length));
}