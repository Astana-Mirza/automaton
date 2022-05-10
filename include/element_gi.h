#ifndef ELEMENT_GI_H
#define ELEMENT_GI_H

#include <QGraphicsItem>

class ElementGI : public QGraphicsItem
{
public:
     virtual ~ElementGI() = default;
     virtual void set_input ( ElementGI* input  ) { input_ = input; }
     virtual void set_output( ElementGI* output ) { output_ = output; }

     bool is_input_set()  const { return input_; }
     bool is_output_set() const { return output_; }

     ElementGI* get_input()  const { return input_; }
     ElementGI* get_output() const { return output_; }

private:
     ElementGI* input_  = nullptr;
     ElementGI* output_ = nullptr;
};

#endif // ELEMENT_GI_H
