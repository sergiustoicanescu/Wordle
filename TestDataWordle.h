#include "TestsWordle.h"

namespace TestPacat
{
  TestMainData mainData = { "pacat", true, 6, {"valid", "invalid", "valid", "invalid", "invalid", "valid"}, true };

  CuvinteValide cuvinteValide[] = {
    {"soare", "a", "", "ggpgg"},
    {"aceea", "ac", "", "ppggp"},
    {"pacat", "", "acpt", "vvvvv"}
  };

  CuvinteInvalide cuvinteInvalide[]
  {
    {"acasaa", "prea lung", "", '\0', '\0'},
    {"aaaaa", "corect", "nu exista", '\0', '\0'},
    {"atent", "corect", "corect", "ac", ""}
  };
}

namespace TestZeama
{
  TestMainData mainData = { "zeama", true, 3, {"valid", "valid", "valid"}, true };

  CuvinteValide cuvinteValide[] = {
    {"acasa", "", "a", "ggvgv"},
    {"amara", "m", "a", "gpvgv"},
    {"zeama", "", "aemz", "vvvvv"}
  };

}

namespace TestMorar
{
  TestMainData mainData = { "morar", true, 4, {"valid", "valid", "valid", "valid"}, true};

  CuvinteValide cuvinteValide[] = {
    {"soare", "ar", "o", "gvppg"},
    {"vorba", "a", "or", "gvvgp"},
    {"torta", "a", "or", "gvvgp"},
    {"morar", "", "amor", "vvvvv"}
  };

}

namespace TestPalid
{
  TestMainData mainData = { "palid", true, 6, {"valid", "valid", "valid", "valid", "valid", "valid"}, false};

  CuvinteValide cuvinteValide[] = {
    {"soare", "a", "", "ggpgg"},
    {"acasa", "a", "", "pgggg"},
    {"barul", "l", "a", "gvggp"},
    {"lacul", "l", "a", "pvggg"},
    {"malin", "", "ail", "gvvvg"},
    {"palit", "", "ailp", "vvvvg"}
  };

}

namespace TestMacaz
{
  TestMainData mainData = { "macaz", true, 6, {"valid", "valid", "valid", "valid", "valid", "valid"}, true };

  CuvinteValide cuvinteValide[] = {
    {"soare", "a", "", "ggpgg"},
    {"afara", "a", "", "pgpgg"},
    {"cafea", "c", "a", "pvggp"},
    {"hamac", "cm", "a", "gvpvp"},
    {"tacam", "m", "ac", "gvvvp"},
    {"macaz", "", "acmz", "vvvvv"}
  };

}


namespace TestValva
{
  TestMainData mainData = { "valva", true, 4, {"valid", "valid", "valid", "valid"}, true };

  CuvinteValide cuvinteValide[] = {
    {"soare", "a", "", "ggpgg"},
    {"afara", "", "a", "pgggv"},
    {"plata", "l", "a", "gppgv"},
    {"valva", "", "alv", "vvvvv"}
  };

}

namespace TestAceea
{
  TestMainData mainData = { "aceea", true, 4, {"valid", "valid", "invalid", "valid"},  true};

  CuvinteValide cuvinteValide[] = {
    {"soare", "ae", "", "ggpgp"},
    {"atent", "", "ae", "vgvgg"},
    {"aceea", "", "ace", "vvvvv"}
  };

  CuvinteInvalide cuvinteInvalide[]
  {
    {"eleva", "corect", "corect", "", "a"}
  };
}

namespace TestAudia
{
  TestMainData mainData = { "audia", true, 4, {"valid", "invalid", "invalid", "valid"},  true};

  CuvinteValide cuvinteValide[] = {
    {"sauas", "au", "", "gpppg"},
    {"audia", "", "adiu", "vvvvv"}
  };

  CuvinteInvalide cuvinteInvalide[]
  {
    {"mitic", "corect", "corect", "au", ""},
    {"agita", "corect", "corect", "u", ""}
  };
}

namespace TestAtlas
{
  TestMainData mainData = { "atlas", true, 5, {"valid", "invalid", "invalid", "invalid", "valid"},  true};

  CuvinteValide cuvinteValide[] = {
    {"atrag", "", "at", "vvgvg"},
    {"atlas", "", "alst", "vvvvv"}
  };

  CuvinteInvalide cuvinteInvalide[]
  {
    {"gauri", "corect", "corect", "", "at"},
    {"acasa", "corect", "corect", "", "at"},
    {"altar", "corect", "corect", "", "t"}
  };
}
