//
// Created by Jacklone on 2017/7/18.
//

#include "Extractor.h"

using namespace nocode::extractapi;
using namespace grpc;
using namespace std;
using namespace familia;

void get_n_gram_sentence(const vector<string>& content, vector<vector<string> >& sentences, int ngram=5) {
  sentences.push_back(vector<string>());
  for (int i = 0; i < content.size(); ++i) {
    sentences.back().push_back(content[i]);
    if (i % ngram == 0) {
      sentences.back().push_back(content[i]);
    }
  }
  return;
}

Extractor::~Extractor() {

}

grpc::Status Extractor::doLda(::grpc::ServerContext *context,
                              const ::nocode::extractapi::LdaRequest *request,
                              ::nocode::extractapi::LdaReply *response) {

  const News news = request->news();

  vector<string> title_seg, content_seg;
  tokenizer_ptr->tokenize(news.title(), title_seg);
  tokenizer_ptr->tokenize(news.content(), content_seg);

  vector<familia::Topic> topics;

  if (engine_ptr->model_type() == familia::ModelType::LDA) {
    LDADoc doc;
    engine_ptr->infer(title_seg, content_seg, doc);
    doc.sparse_topic_dist(topics);

  } else {
    SLDADoc doc;
    vector<vector<string> > title_ngram, content_ngram;
    get_n_gram_sentence(title_seg, title_ngram, 5);
    get_n_gram_sentence(content_seg, content_ngram, 5);

    engine_ptr->infer(title_ngram, content_ngram, doc);
    doc.sparse_topic_dist(topics);
  }

  for (auto tpc: topics) {
    LdaTopic *topic = response->add_topics();
    topic->set_tid(tpc.tid);
    topic->set_prob(tpc.prob);
  }
  response->set_error("");

  return Status::OK;
}

Extractor::Extractor(std::shared_ptr<familia::InferenceEngine> inferenceEngine,
                     std::shared_ptr<familia::Tokenizer> tokenizer)
  : engine_ptr(inferenceEngine),
    tokenizer_ptr(tokenizer)
{

}
