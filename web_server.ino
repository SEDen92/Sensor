const int sunset_start = 17;
const int sunset_stop = 8;

String IndexPage() {
  float Temperature = GET_TEMPERATURE();
  float Pressure = GET_PRESSURE();
  String Page;
  Page += "<!doctype html>";
  Page += "<html lang=\"ru\"><head>";
  Page += "<meta charset=\"utf-8\">";
  Page += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=yes\">";
  Page += "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">";
  Page += "<title>Control block</title></head>";
  if (hour >= sunset_start || hour <= sunset_stop) {
    Page += "<style>body {background: #343a40;}</style><body><br>";
  }
  else  {
    Page += "<body><br>";
  }
  Page += "<div class=\"col-sm\">";
  Page += "<div class=\"tab-content\" id=\"v-pills-tabContent\">";
  Page += "<div class=\"tab-pane fade show active\" id=\"v-pills-home\" role=\"tabpanel\" aria-labelledby=\"v-pills-home-tab\">";
  if (hour >= sunset_start || hour <= sunset_stop) {
    Page += "<div class=\"shadow p-3 mb-5 bg-dark rounded\">";
    Page += "<table class=\"table table-dark\">";
  }
  else  {
    Page += "<div class=\"shadow p-3 mb-5 bg-white rounded\">";
    Page += "<table class=\"table table-white\">";
  }
  Page += "<tbody><tr><td><h1 class=\"display-4\" align=\"center\">Уличный блок управления</h1><h1 class=\"display-4\" align=\"center\">Текущее время</h1><h1 class=\"display-1\" align=\"center\">";
  if (hour > 9) {
    Page += String(hour);
  }
  else  {
    Page += "0" + String(hour);
  }
  Page += ":";
  if (minute > 9) {
    Page += String(minute);
  }
  else  {
    Page += "0" + String(minute);
  }
  if (digitalRead(LEDRelay) == 0)  {
    Page += "</h1><form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/\"><button type=\"submit\" class=\"btn btn-outline-success btn-lg btn-block\" name=\"post\" value=\"relay_on\">Включить светодиодный прожектор</button></form><br>";
  }
  else  {
    Page += "</h1><form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/\"><button type=\"submit\" class=\"btn btn-outline-danger btn-lg btn-block\" name=\"post\" value=\"relay_off\">Выключить светодиодный прожектор</button></form><br>";
  }
  if (LED_Manual_Mode == true)  {
    Page += "</h1><form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/\"><button type=\"submit\" class=\"btn btn-outline-success btn-lg btn-block\" name=\"post\" value=\"manual_mode_off\">Активировать автоматический режим</button>";
  }
  else  {
    Page += "</h1><form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/\"><button type=\"submit\" class=\"btn btn-outline-danger btn-lg btn-block\" name=\"post\" value=\"manual_mode_on\">Активировать ручной режим</button>";
  }
  Page += "<div class=\"col-sm\">";
  Page += "<div class=\"tab-content\" id=\"v-pills-tabContent\">";
  Page += "<div class=\"tab-pane fade show active\" id=\"v-pills-home\" role=\"tabpanel\" aria-labelledby=\"v-pills-home-tab\">";
  if (hour >= sunset_start || hour <= sunset_stop) {
    Page += "<div class=\"shadow p-3 mb-5 bg-dark rounded\">";
    Page += "<table class=\"table table-dark\"><tbody>";
  }
  else  {
    Page += "<div class=\"shadow p-3 mb-5 bg-white rounded\">";
    Page += "<table class=\"table table-white\"><tbody>";
  }
  Page += "<p class=\"font-weight-light\"  align=\"center\" style=\"font-size:200%\">Данные с датчиков</p><tr><td>";
  Page += "<h1 class=\"display-4\" align=\"left\">Температура</h1>";
  if (Frost == false) {
    Page += "<h1 class=\"display-2 text-danger\" align=\"left\">";
  }
  else  {
    Page += "<h1 class=\"display-2 text-info\" align=\"left\">";
  }
  if (Temperature > 0)  {
    Page += "+" + String(Temperature).substring(0, String(Temperature).length() - 1) + " C";
  }
  else  {
    Page += String(Temperature).substring(0, String(Temperature).length() - 1) + " C";
  }
  Page += "</h1></td><td>";
  Page += "<h1 class=\"display-4\" align=\"right\">Атмосферное давление</h1>";
  Page += "<h1 class=\"display-2\" style=\"color:#ff00ff\" align=\"right\">";
  Page += String(Pressure).substring(0, String(Pressure).length() - 1) + " мм.рт.ст.";
  Page += "</h1></td></tr></tbody></table></div></table>";
  Page += "</td></tr></tbody></table></div></table>";
  Page += "<script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script>";
  Page += "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\" integrity=\"sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1\" crossorigin=\"anonymous\"></script>";
  Page += "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\" integrity=\"sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM\" crossorigin=\"anonymous\"></script>";
  Page += "<br><br><br><br><br></body></html>";
  return Page;
}

String AdminPage() {
  String Page;
  Page += "<!doctype html>";
  return Page;
}

void WEBPost(String post_message) {
  if (post_message == "relay_on") SWITCH_RELAY(true, true);
  if (post_message == "relay_off") SWITCH_RELAY(false, true);
  if (post_message == "manual_mode_on") LED_Manual_Mode = true;
  if (post_message == "manual_mode_off") LED_Manual_Mode = false;
  CHECK_TIME();
}

void WEBNotFound()  {
  String Page;
  Page += "<!doctype html><html lang=\"ru\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, shrink-to-fit=yes\">";
  Page += "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\">";
  Page += "<title>WIFI Fan</title></head>";
  if (hour >= sunset_start || hour <= sunset_stop) {
    Page += "<style>body {background: #343a40;}</style><body><br><br><br><br><br>";
  }
  else  {
    Page += "<body><br><br><br><br><br>";
  }
  Page += "<div class=\"col-sm\"><div class=\"tab-content\" id=\"v-pills-tabContent\"><div class=\"tab-pane fade show active\" id=\"v-pills-home\" role=\"tabpanel\" aria-labelledby=\"v-pills-home-tab\">";
  if (hour >= sunset_start || hour <= sunset_stop) {
    Page += "<div class=\"shadow p-3 mb-5 bg-dark rounded\">";
    Page += "<table class=\"table table-dark\"><tbody>";
  }
  else  {
    Page += "<div class=\"shadow p-3 mb-5 bg-white rounded\">";
    Page += "<table class=\"table table-white\"><tbody>";
  }
  Page += "<tbody><tr><td><h1 class=\"display-1\" align=\"center\">404 Not found!</h1>";
  Page += "<p class=\"font-weight-light\" align=\"center\" style=\"font-size:200%\">Страница не найдена!</p>";
  Page += "<p class=\"font-weight-light\" align=\"center\" style=\"font-size:200%\">Page not found!</p>";
  Page += "<form method=\"post\" enctype=\"text/plain\" action=\"/\"><button type=\"submit\" class=\"btn btn-outline-secondary btn-lg btn-block\" value=\"Submit\">На главную</button></form></td></tr></tbody></table></div></table>";
  Page += "<script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script>";
  Page += "<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\" integrity=\"sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1\" crossorigin=\"anonymous\"></script>";
  Page += "<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\" integrity=\"sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM\" crossorigin=\"anonymous\"></script>";
  Page += "<br><br><br><br><br></body></html>";
  server.send(404, "text/html", Page);
}

void WEBServer()  {
  server.on("/", []() {
    //if (!server.authenticate(web_login, web_password))
    //  return server.requestAuthentication();
    WEBPost(server.arg("post"));
    server.send(200, "text/html", IndexPage());
  });
  server.on("/admin", []() {
    if (!server.authenticate("admin", "0000"))
      return server.requestAuthentication();
    WEBPost(server.arg("post"));
    server.send(200, "text/html", AdminPage());
  });
  server.onNotFound(WEBNotFound);
  server.begin();
}
