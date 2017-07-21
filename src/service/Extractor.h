//
// Created by Jacklone on 2017/7/18.
//

#ifndef FAMILIA_EXTRACTOR_H
#define FAMILIA_EXTRACTOR_H

#include <familia/inference_engine.h>
#include <familia/tokenizer.h>
#include "familiaapi.pb.h"
#include "familiaapi.grpc.pb.h"


class Extractor final : public nocode::extractapi::FamiliaApi::Service {
 public:
  Extractor(std::shared_ptr<familia::InferenceEngine> inferenceEngine,
            std::shared_ptr<familia::Tokenizer> tokenizer);
  virtual ~Extractor();

  grpc::Status doLda(::grpc::ServerContext *context,
                     const ::nocode::extractapi::LdaRequest *request,
                     ::nocode::extractapi::LdaReply *response) override;

 private:
  std::shared_ptr<familia::InferenceEngine> engine_ptr;

  std::shared_ptr<familia::Tokenizer> tokenizer_ptr;


};

#endif //FAMILIA_EXTRACTOR_H
