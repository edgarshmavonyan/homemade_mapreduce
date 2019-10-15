#include <mapreduce/interface.h>

#include <iostream>
#include <cctype>

template<typename Filter>
std::string Strip(const std::string& string, Filter filter) {
  size_t start = 0;
  for (; start < string.size() && filter(string[start]); ++start);
  if (start == string.size()) {
    return std::string();
  }
  size_t end = string.size() - 1;
  for (; end < string.size() && filter(string[end]); --end);
  return string.substr(start, end - start + 1);
}

class WordCountMapper: public MapperInterface<std::string, size_t> {
 public:
  void Process(Reader& input_reader, Writer& output_writer) override {
    for (; input_reader.IsValid(); input_reader.Next()) {
      auto& text = input_reader.Get();
      std::stringstream text_stream;
      text_stream << text;

      std::string word;
      while (text_stream >> word) {
        word = Strip(word, ispunct);
        std::transform(word.begin(), word.end(), word.begin(),
            [] (char c) {
          return std::tolower(c);
        });
        if (!word.empty()) {
          output_writer.Write({word, 1});
        }
      }
    }
  }
};

class SumValuesReducer: public ReducerInterface<std::string, size_t> {
 public:
 void Process(Reader& input_reader, Writer& output_writer) override {
   size_t count = 0;
   auto& current_key = input_reader.GetKey();
   for (; input_reader.IsValid(); input_reader.Next()) {
     auto& value = input_reader.Get();
     count += value;
   }
   output_writer.Write({current_key, count});
 }
};


int main(int argc, char* argv[]) {
  MapReduceInit();

  WordCountMapper mapper;
  SumValuesReducer reducer;

  RunMapReduce(argc, argv, mapper, reducer);

  MapReduceFinalize();
  return 0;
}