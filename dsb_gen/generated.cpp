
#include <simgrid/s4u/Actor.hpp>
#include <simgrid/s4u/Host.hpp>
#include <simgrid/s4u/Mailbox.hpp>
#include <simgrid/s4u/Engine.hpp>
#include <simgrid/s4u/Comm.hpp>
#include "ElasticPolicy.hpp"
#include "ElasticTask.hpp"
#include "DataSource.hpp"
#include <memory>

XBT_LOG_NEW_DEFAULT_CATEGORY(run_log, "logs of the experiment");

int outSizes(RequestType, std::string);
/* RETURN FUNCTIONS, AUTO GENERATED CODE, MODIFY IF YOU KNOW WHAT YOU WANT */
    void return_nginx_web_server(TaskDescription* td) {
      XBT_DEBUG("Return function of service nginx_web_server");
      switch (td->requestType)
      {
case RequestType::COMPOSE:
      if(td->nbHops == 1){
        XBT_DEBUG("Output Function for nginx_web_server (PARALLEL CHILDS)");
        std::vector<simgrid::s4u::CommPtr> comV;
        simgrid::s4u::CommPtr com;

          XBT_DEBUG("Put to media_service");
          s4u_Mailbox* m_media_service = s4u_Mailbox::by_name("media_service");
          TaskDescription* td_0 = new TaskDescription(*td);
          td_0->requestType = RequestType::COMPOSE_0;
          com = m_media_service->put_async(td_0, outSizes(td_0->requestType, "media_service"));
          comV.push_back(com);

          XBT_DEBUG("Put to user_service");
          s4u_Mailbox* m_user_service = s4u_Mailbox::by_name("user_service");
          TaskDescription* td_1 = new TaskDescription(*td);
          td_1->requestType = RequestType::COMPOSE_1;
          com = m_user_service->put_async(td_1, outSizes(td_1->requestType, "user_service"));
          comV.push_back(com);

          XBT_DEBUG("Put to text_service");
          s4u_Mailbox* m_text_service = s4u_Mailbox::by_name("text_service");
          TaskDescription* td_2 = new TaskDescription(*td);
          td_2->requestType = RequestType::COMPOSE_2;
          com = m_text_service->put_async(td_2, outSizes(td_2->requestType, "text_service"));
          comV.push_back(com);

          XBT_DEBUG("Put to unique_id_service");
          s4u_Mailbox* m_unique_id_service = s4u_Mailbox::by_name("unique_id_service");
          TaskDescription* td_3 = new TaskDescription(*td);
          td_3->requestType = RequestType::COMPOSE_3;
          com = m_unique_id_service->put_async(td_3, outSizes(td_3->requestType, "unique_id_service"));
          comV.push_back(com);

simgrid::s4u::Comm::wait_all(&comV); // wait for communications to finish
break;
}
	}
}
    void return_media_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service media_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_0:
      if(td->nbHops == 2){
        XBT_DEBUG("Output Function for COMPOSE_0, put to compose_post_service");
        s4u_Mailbox* m_compose_post_service = s4u_Mailbox::by_name("compose_post_service");
        m_compose_post_service->put(td, outSizes(td->requestType, "compose_post_service"));


break;
}

break;
	}
}
    void return_compose_post_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service compose_post_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_0:
      if(td->nbHops == 3){
        XBT_DEBUG("Output Function for COMPOSE_0, Final service, DELETE");
        for (auto it = td->parentSpans.rbegin(); it != td->parentSpans.rend(); ++it)
  {
    if((*it)->get() != NULL){
    auto t2 = std::chrono::seconds(946684800)+std::chrono::microseconds(int(simgrid::s4u::Engine::get_instance()->get_clock()*1000000));
    (*it)->get()->Log({{"end",t2.count()}});
    (*it)->get()->Finish({opentracing::v3::FinishTimestamp(t2)});
    (*it)->reset();
    (*it) == NULL;
    }
  }
        delete td;
        // TODO DELETE JAEGER SPANS
      }

break;


case RequestType::COMPOSE_1:
      if(td->nbHops == 3){
        XBT_DEBUG("Output Function for COMPOSE_1, Final service, DELETE");
        for (auto it = td->parentSpans.rbegin(); it != td->parentSpans.rend(); ++it)
  {
    if((*it)->get() != NULL){
    auto t2 = std::chrono::seconds(946684800)+std::chrono::microseconds(int(simgrid::s4u::Engine::get_instance()->get_clock()*1000000));
    (*it)->get()->Log({{"end",t2.count()}});
    (*it)->get()->Finish({opentracing::v3::FinishTimestamp(t2)});
    (*it)->reset();
    (*it) == NULL;
    }
  }
        delete td;
        // TODO DELETE JAEGER SPANS
      }

break;


case RequestType::COMPOSE_2_0:
      if(td->nbHops == 4){
        XBT_DEBUG("Output Function for COMPOSE_2_0, Final service, DELETE");
        for (auto it = td->parentSpans.rbegin(); it != td->parentSpans.rend(); ++it)
  {
    if((*it)->get() != NULL){
    auto t2 = std::chrono::seconds(946684800)+std::chrono::microseconds(int(simgrid::s4u::Engine::get_instance()->get_clock()*1000000));
    (*it)->get()->Log({{"end",t2.count()}});
    (*it)->get()->Finish({opentracing::v3::FinishTimestamp(t2)});
    (*it)->reset();
    (*it) == NULL;
    }
  }
        delete td;
        // TODO DELETE JAEGER SPANS
      }

break;


case RequestType::COMPOSE_2_1:
      if(td->nbHops == 4){
        XBT_DEBUG("Output Function for COMPOSE_2_1, put to post_storage_service");
        s4u_Mailbox* m_post_storage_service = s4u_Mailbox::by_name("post_storage_service");
        m_post_storage_service->put(td, outSizes(td->requestType, "post_storage_service"));


break;
}

break;



case RequestType::COMPOSE_2_2:
    if(td->nbHops == 3){
      XBT_DEBUG("Output Function compose_post_service (FINAL NODE, NO CHILD!)");
      // TODO DELETE
              for (auto it = td->parentSpans.rbegin(); it != td->parentSpans.rend(); ++it)
  {
    if((*it)->get() != NULL){
    auto t2 = std::chrono::seconds(946684800)+std::chrono::microseconds(int(simgrid::s4u::Engine::get_instance()->get_clock()*1000000));
    (*it)->get()->Log({{"end",t2.count()}});
    (*it)->get()->Finish({opentracing::v3::FinishTimestamp(t2)});
    (*it)->reset();
    (*it) == NULL;
    }
  }
    }

break;


case RequestType::COMPOSE_3:
      if(td->nbHops == 3){
        XBT_DEBUG("Output Function for COMPOSE_3, Final service, DELETE");
        for (auto it = td->parentSpans.rbegin(); it != td->parentSpans.rend(); ++it)
  {
    if((*it)->get() != NULL){
    auto t2 = std::chrono::seconds(946684800)+std::chrono::microseconds(int(simgrid::s4u::Engine::get_instance()->get_clock()*1000000));
    (*it)->get()->Log({{"end",t2.count()}});
    (*it)->get()->Finish({opentracing::v3::FinishTimestamp(t2)});
    (*it)->reset();
    (*it) == NULL;
    }
  }
        delete td;
        // TODO DELETE JAEGER SPANS
      }

break;
	}
}
    void return_user_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service user_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_1:
      if(td->nbHops == 2){
        XBT_DEBUG("Output Function for COMPOSE_1, put to compose_post_service");
        s4u_Mailbox* m_compose_post_service = s4u_Mailbox::by_name("compose_post_service");
        m_compose_post_service->put(td, outSizes(td->requestType, "compose_post_service"));


break;
}

break;
	}
}
    void return_text_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service text_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2:
      if(td->nbHops == 2){
        XBT_DEBUG("Output Function for text_service (PARALLEL CHILDS)");
        std::vector<simgrid::s4u::CommPtr> comV;
        simgrid::s4u::CommPtr com;

          XBT_DEBUG("Put to url_shorten_service");
          s4u_Mailbox* m_url_shorten_service = s4u_Mailbox::by_name("url_shorten_service");
          TaskDescription* td_0 = new TaskDescription(*td);
          td_0->requestType = RequestType::COMPOSE_2_0;
          com = m_url_shorten_service->put_async(td_0, outSizes(td_0->requestType, "url_shorten_service"));
          comV.push_back(com);

          XBT_DEBUG("Put to user_mention_service");
          s4u_Mailbox* m_user_mention_service = s4u_Mailbox::by_name("user_mention_service");
          TaskDescription* td_1 = new TaskDescription(*td);
          td_1->requestType = RequestType::COMPOSE_2_1;
          com = m_user_mention_service->put_async(td_1, outSizes(td_1->requestType, "user_mention_service"));
          comV.push_back(com);

          XBT_DEBUG("Put to compose_post_service");
          s4u_Mailbox* m_compose_post_service = s4u_Mailbox::by_name("compose_post_service");
          TaskDescription* td_2 = new TaskDescription(*td);
          td_2->requestType = RequestType::COMPOSE_2_2;
          com = m_compose_post_service->put_async(td_2, outSizes(td_2->requestType, "compose_post_service"));
          comV.push_back(com);

simgrid::s4u::Comm::wait_all(&comV); // wait for communications to finish
break;
}
	}
}
    void return_url_shorten_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service url_shorten_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_0:
      if(td->nbHops == 3){
        XBT_DEBUG("Output Function for COMPOSE_2_0, put to compose_post_service");
        s4u_Mailbox* m_compose_post_service = s4u_Mailbox::by_name("compose_post_service");
        m_compose_post_service->put(td, outSizes(td->requestType, "compose_post_service"));


break;
}

break;
	}
}
    void return_user_mention_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service user_mention_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 3){
        XBT_DEBUG("Output Function for COMPOSE_2_1, put to compose_post_service");
        s4u_Mailbox* m_compose_post_service = s4u_Mailbox::by_name("compose_post_service");
        m_compose_post_service->put(td, outSizes(td->requestType, "compose_post_service"));


break;
}

break;
	}
}
    void return_post_storage_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service post_storage_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 5){
        XBT_DEBUG("Output Function for COMPOSE_2_1, put to user_timeline_service");
        s4u_Mailbox* m_user_timeline_service = s4u_Mailbox::by_name("user_timeline_service");
        m_user_timeline_service->put(td, outSizes(td->requestType, "user_timeline_service"));


break;
}

break;
	}
}
    void return_user_timeline_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service user_timeline_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 6){
        XBT_DEBUG("Output Function for COMPOSE_2_1, put to write_home_timeline_service");
        s4u_Mailbox* m_write_home_timeline_service = s4u_Mailbox::by_name("write_home_timeline_service");
        m_write_home_timeline_service->put(td, outSizes(td->requestType, "write_home_timeline_service"));


break;
}

break;
	}
}
    void return_write_home_timeline_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service write_home_timeline_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 7){
        XBT_DEBUG("Output Function for COMPOSE_2_1, put to social_graph_service");
        s4u_Mailbox* m_social_graph_service = s4u_Mailbox::by_name("social_graph_service");
        m_social_graph_service->put(td, outSizes(td->requestType, "social_graph_service"));


break;
}

      if(td->nbHops == 9){
        XBT_DEBUG("Output Function for COMPOSE_2_1, Final service, DELETE");
        for (auto it = td->parentSpans.rbegin(); it != td->parentSpans.rend(); ++it)
  {
    if((*it)->get() != NULL){
    auto t2 = std::chrono::seconds(946684800)+std::chrono::microseconds(int(simgrid::s4u::Engine::get_instance()->get_clock()*1000000));
    (*it)->get()->Log({{"end",t2.count()}});
    (*it)->get()->Finish({opentracing::v3::FinishTimestamp(t2)});
    (*it)->reset();
    (*it) == NULL;
    }
  }
        delete td;
        // TODO DELETE JAEGER SPANS
      }

break;
	}
}
    void return_social_graph_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service social_graph_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 8){
        XBT_DEBUG("Output Function for COMPOSE_2_1, put to write_home_timeline_service");
        s4u_Mailbox* m_write_home_timeline_service = s4u_Mailbox::by_name("write_home_timeline_service");
        m_write_home_timeline_service->put(td, outSizes(td->requestType, "write_home_timeline_service"));


break;
}

break;
	}
}
    void return_unique_id_service(TaskDescription* td) {
      XBT_DEBUG("Return function of service unique_id_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_3:
      if(td->nbHops == 2){
        XBT_DEBUG("Output Function for COMPOSE_3, put to compose_post_service");
        s4u_Mailbox* m_compose_post_service = s4u_Mailbox::by_name("compose_post_service");
        m_compose_post_service->put(td, outSizes(td->requestType, "compose_post_service"));


break;
}

break;
	}
}
/* PR FUNCTIONS, AUTO GENERATED CODE, MODIFY IF YOU KNOW WHAT YOU WANT */
    double pr_nginx_web_server(TaskDescription* td) {
      XBT_DEBUG("pr function of service nginx_web_server");
      switch (td->requestType)
      {
case RequestType::COMPOSE:
      if(td->nbHops == 1){XBT_DEBUG("Entered cost Function for nginx_web_server"); return 8419000;
}
break;

      	}//it should never end up here
return -1;
}
    double pr_media_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service media_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_0:
      if(td->nbHops == 2){XBT_DEBUG("Entered cost Function for COMPOSE_0"); return 279000;}

break;
	}//it should never end up here
return -1;
}
    double pr_compose_post_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service compose_post_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_0:
      if(td->nbHops == 3){XBT_DEBUG("Entered cost Function for COMPOSE_0 (FINAL NODE, NO CHILD!)"); return 346000;}

break;


case RequestType::COMPOSE_1:
      if(td->nbHops == 3){XBT_DEBUG("Entered cost Function for COMPOSE_1 (FINAL NODE, NO CHILD!)"); return 323000;}

break;


case RequestType::COMPOSE_2_0:
      if(td->nbHops == 4){XBT_DEBUG("Entered cost Function for COMPOSE_2_0 (FINAL NODE, NO CHILD!)"); return 214000;}

break;


case RequestType::COMPOSE_2_1:
      if(td->nbHops == 4){XBT_DEBUG("Entered cost Function for COMPOSE_2_1"); return 1068000;}

break;



case RequestType::COMPOSE_2_2:
    if(td->nbHops == 3){XBT_DEBUG("Entered cost Function for compose_post_service"); return 224000;}

break;


case RequestType::COMPOSE_3:
      if(td->nbHops == 3){XBT_DEBUG("Entered cost Function for COMPOSE_3 (FINAL NODE, NO CHILD!)"); return 287000;}

break;
	}//it should never end up here
return -1;
}
    double pr_user_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service user_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_1:
      if(td->nbHops == 2){XBT_DEBUG("Entered cost Function for COMPOSE_1"); return 262000;}

break;
	}//it should never end up here
return -1;
}
    double pr_text_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service text_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2:
      if(td->nbHops == 2){XBT_DEBUG("Entered cost Function for text_service"); return 1852000;
}
break;

      	}//it should never end up here
return -1;
}
    double pr_url_shorten_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service url_shorten_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_0:
      if(td->nbHops == 3){XBT_DEBUG("Entered cost Function for COMPOSE_2_0"); return 365000;}

break;
	}//it should never end up here
return -1;
}
    double pr_user_mention_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service user_mention_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 3){XBT_DEBUG("Entered cost Function for COMPOSE_2_1"); return 1506000;}

break;
	}//it should never end up here
return -1;
}
    double pr_post_storage_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service post_storage_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 5){XBT_DEBUG("Entered cost Function for COMPOSE_2_1"); return 481000;}

break;
	}//it should never end up here
return -1;
}
    double pr_user_timeline_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service user_timeline_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 6){XBT_DEBUG("Entered cost Function for COMPOSE_2_1"); return 1423000;}

break;
	}//it should never end up here
return -1;
}
    double pr_write_home_timeline_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service write_home_timeline_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 7){XBT_DEBUG("Entered cost Function for COMPOSE_2_1"); return 476000;}

      if(td->nbHops == 9){XBT_DEBUG("Entered cost Function for COMPOSE_2_1 (FINAL NODE, NO CHILD!)"); return 13000;}

break;
	}//it should never end up here
return -1;
}
    double pr_social_graph_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service social_graph_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_2_1:
      if(td->nbHops == 8){XBT_DEBUG("Entered cost Function for COMPOSE_2_1"); return 702000;}

break;
	}//it should never end up here
return -1;
}
    double pr_unique_id_service(TaskDescription* td) {
      XBT_DEBUG("pr function of service unique_id_service");
      switch (td->requestType)
      {
case RequestType::COMPOSE_3:
      if(td->nbHops == 2){XBT_DEBUG("Entered cost Function for COMPOSE_3"); return 241000;}

break;
	}//it should never end up here
return -1;
}
int outSizes(RequestType t, std::string nextServ){
    switch (t)
{	case RequestType::COMPOSE :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
	case RequestType::COMPOSE_0 :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
	case RequestType::COMPOSE_1 :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
	case RequestType::COMPOSE_2 :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
	case RequestType::COMPOSE_2_0 :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
	case RequestType::COMPOSE_2_1 :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
	case RequestType::COMPOSE_2_2 :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
	case RequestType::COMPOSE_3 :
	if(nextServ == "media_service"){return 476;}
	if(nextServ == "compose_post_service"){return 740;}
	if(nextServ == "user_service"){return 466;}
	if(nextServ == "text_service"){return 1278;}
	if(nextServ == "url_shorten_service"){return 728;}
	if(nextServ == "user_mention_service"){return 1053;}
	if(nextServ == "post_storage_service"){return 1359;}
	if(nextServ == "user_timeline_service"){return 804;}
	if(nextServ == "write_home_timeline_service"){return 246;}
	if(nextServ == "social_graph_service"){return 525;}
	if(nextServ == "unique_id_service"){return 428;}
	break;
}return -1; // WE SHOULD NEVER GET TO THAT POINT
}

std::string reqTypeToStr(RequestType t){
    switch (t)
{	case RequestType::COMPOSE : return "COMPOSE";break;
	case RequestType::COMPOSE_0 : return "COMPOSE_0";break;
	case RequestType::COMPOSE_1 : return "COMPOSE_1";break;
	case RequestType::COMPOSE_2 : return "COMPOSE_2";break;
	case RequestType::COMPOSE_2_0 : return "COMPOSE_2_0";break;
	case RequestType::COMPOSE_2_1 : return "COMPOSE_2_1";break;
	case RequestType::COMPOSE_2_2 : return "COMPOSE_2_2";break;
	case RequestType::COMPOSE_3 : return "COMPOSE_3";break;
}return "WTF";
}

  void run(std::map<std::string, std::string> m) {
    XBT_INFO("Starting run()");
    std::string posS;
    // create ETM for service nginx_web_server
    std::vector<std::string> v_serv_nginx_web_server = std::vector<std::string>();
    v_serv_nginx_web_server.push_back("nginx_web_server");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_nginx_web_server = std::make_shared<simgrid::s4u::ElasticTaskManager>("nginx_web_server",v_serv_nginx_web_server);
    serv_nginx_web_server->setBootDuration(0);
    serv_nginx_web_server->setDataSizeRatio(1);
    serv_nginx_web_server->setParallelTasksPerInst(50);
    serv_nginx_web_server->setOutputFunction(return_nginx_web_server);
    serv_nginx_web_server->setProcessRatioFunc(pr_nginx_web_server);
    serv_nginx_web_server->setReqNames(reqTypeToStr);
    if (m.find("nginx_web_server") != m.end()) {
        posS = m.find("nginx_web_server")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("nginx_web_server on %s", posS.c_str() );
    serv_nginx_web_server->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_nginx_web_server", simgrid::s4u::Host::by_name(posS), [serv_nginx_web_server] { serv_nginx_web_server->run(); });


    // create ETM for service media_service
    std::vector<std::string> v_serv_media_service = std::vector<std::string>();
    v_serv_media_service.push_back("media_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_media_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("media_service",v_serv_media_service);
    serv_media_service->setBootDuration(0);
    serv_media_service->setDataSizeRatio(1);
    serv_media_service->setParallelTasksPerInst(50);
    serv_media_service->setOutputFunction(return_media_service);
    serv_media_service->setProcessRatioFunc(pr_media_service);
    serv_media_service->setReqNames(reqTypeToStr);
    if (m.find("media_service") != m.end()) {
        posS = m.find("media_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("media_service on %s", posS.c_str());
    serv_media_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_media_service", simgrid::s4u::Host::by_name(posS), [serv_media_service] { serv_media_service->run(); });


    // create ETM for service compose_post_service
    std::vector<std::string> v_serv_compose_post_service = std::vector<std::string>();
    v_serv_compose_post_service.push_back("compose_post_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_compose_post_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("compose_post_service",v_serv_compose_post_service);
    serv_compose_post_service->setBootDuration(0);
    serv_compose_post_service->setDataSizeRatio(1);
    serv_compose_post_service->setParallelTasksPerInst(50);
    serv_compose_post_service->setOutputFunction(return_compose_post_service);
    serv_compose_post_service->setProcessRatioFunc(pr_compose_post_service);
    serv_compose_post_service->setReqNames(reqTypeToStr);
        if (m.find("compose_post_service") != m.end()) {
        posS = m.find("compose_post_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("compose_post_service on %s", posS.c_str());
    serv_compose_post_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_compose_post_service", simgrid::s4u::Host::by_name(posS), [serv_compose_post_service] { serv_compose_post_service->run(); });


    // create ETM for service user_service
    std::vector<std::string> v_serv_user_service = std::vector<std::string>();
    v_serv_user_service.push_back("user_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_user_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("user_service",v_serv_user_service);
    serv_user_service->setBootDuration(0);
    serv_user_service->setDataSizeRatio(1);
    serv_user_service->setParallelTasksPerInst(50);
    serv_user_service->setOutputFunction(return_user_service);
    serv_user_service->setProcessRatioFunc(pr_user_service);
    serv_user_service->setReqNames(reqTypeToStr);
    if (m.find("user_service") != m.end()) {
        posS = m.find("user_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("user_service on %s", posS.c_str());
    serv_user_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_user_service", simgrid::s4u::Host::by_name(posS), [serv_user_service] { serv_user_service->run(); });


    // create ETM for service text_service
    std::vector<std::string> v_serv_text_service = std::vector<std::string>();
    v_serv_text_service.push_back("text_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_text_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("text_service",v_serv_text_service);
    serv_text_service->setBootDuration(0);
    serv_text_service->setDataSizeRatio(1);
    serv_text_service->setParallelTasksPerInst(50);
    serv_text_service->setOutputFunction(return_text_service);
    serv_text_service->setProcessRatioFunc(pr_text_service);
    serv_text_service->setReqNames(reqTypeToStr);
    if (m.find("text_service") != m.end()) {
        posS = m.find("text_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("text_service on %s", posS.c_str());
    serv_text_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_text_service", simgrid::s4u::Host::by_name(posS), [serv_text_service] { serv_text_service->run(); });


    // create ETM for service url_shorten_service
    std::vector<std::string> v_serv_url_shorten_service = std::vector<std::string>();
    v_serv_url_shorten_service.push_back("url_shorten_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_url_shorten_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("url_shorten_service",v_serv_url_shorten_service);
    serv_url_shorten_service->setBootDuration(0);
    serv_url_shorten_service->setDataSizeRatio(1);
    serv_url_shorten_service->setParallelTasksPerInst(50);
    serv_url_shorten_service->setOutputFunction(return_url_shorten_service);
    serv_url_shorten_service->setProcessRatioFunc(pr_url_shorten_service);
    serv_url_shorten_service->setReqNames(reqTypeToStr);
        if (m.find("url_shorten_service") != m.end()) {
        posS = m.find("url_shorten_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("url_shorten_service on %s", posS.c_str());
    serv_url_shorten_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_url_shorten_service", simgrid::s4u::Host::by_name(posS), [serv_url_shorten_service] { serv_url_shorten_service->run(); });


    // create ETM for service user_mention_service
    std::vector<std::string> v_serv_user_mention_service = std::vector<std::string>();
    v_serv_user_mention_service.push_back("user_mention_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_user_mention_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("user_mention_service",v_serv_user_mention_service);
    serv_user_mention_service->setBootDuration(0);
    serv_user_mention_service->setDataSizeRatio(1);
    serv_user_mention_service->setParallelTasksPerInst(50);
    serv_user_mention_service->setOutputFunction(return_user_mention_service);
    serv_user_mention_service->setProcessRatioFunc(pr_user_mention_service);
    serv_user_mention_service->setReqNames(reqTypeToStr);
    if (m.find("user_mention_service") != m.end()) {
        posS = m.find("user_mention_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("user_mention_service on %s", posS.c_str());
    serv_user_mention_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_user_mention_service", simgrid::s4u::Host::by_name(posS), [serv_user_mention_service] { serv_user_mention_service->run(); });


    // create ETM for service post_storage_service
    std::vector<std::string> v_serv_post_storage_service = std::vector<std::string>();
    v_serv_post_storage_service.push_back("post_storage_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_post_storage_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("post_storage_service",v_serv_post_storage_service);
    serv_post_storage_service->setBootDuration(0);
    serv_post_storage_service->setDataSizeRatio(1);
    serv_post_storage_service->setParallelTasksPerInst(50);
    serv_post_storage_service->setOutputFunction(return_post_storage_service);
    serv_post_storage_service->setProcessRatioFunc(pr_post_storage_service);
    serv_post_storage_service->setReqNames(reqTypeToStr);
    if (m.find("post_storage_service") != m.end()) {
        posS = m.find("post_storage_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("post_storage_service on %s", posS.c_str());
    serv_post_storage_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_post_storage_service", simgrid::s4u::Host::by_name(posS), [serv_post_storage_service] { serv_post_storage_service->run(); });


    // create ETM for service user_timeline_service
    std::vector<std::string> v_serv_user_timeline_service = std::vector<std::string>();
    v_serv_user_timeline_service.push_back("user_timeline_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_user_timeline_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("user_timeline_service",v_serv_user_timeline_service);
    serv_user_timeline_service->setBootDuration(0);
    serv_user_timeline_service->setDataSizeRatio(1);
    serv_user_timeline_service->setParallelTasksPerInst(50);
    serv_user_timeline_service->setOutputFunction(return_user_timeline_service);
    serv_user_timeline_service->setProcessRatioFunc(pr_user_timeline_service);
    serv_user_timeline_service->setReqNames(reqTypeToStr);
    if (m.find("user_timeline_service") != m.end()) {
        posS = m.find("user_timeline_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("user_timeline_service on %s", posS.c_str());
    serv_user_timeline_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_user_timeline_service", simgrid::s4u::Host::by_name(posS), [serv_user_timeline_service] { serv_user_timeline_service->run(); });


    // create ETM for service write_home_timeline_service
    std::vector<std::string> v_serv_write_home_timeline_service = std::vector<std::string>();
    v_serv_write_home_timeline_service.push_back("write_home_timeline_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_write_home_timeline_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("write_home_timeline_service",v_serv_write_home_timeline_service);
    serv_write_home_timeline_service->setBootDuration(0);
    serv_write_home_timeline_service->setDataSizeRatio(1);
    serv_write_home_timeline_service->setParallelTasksPerInst(50);
    serv_write_home_timeline_service->setOutputFunction(return_write_home_timeline_service);
    serv_write_home_timeline_service->setProcessRatioFunc(pr_write_home_timeline_service);
    serv_write_home_timeline_service->setReqNames(reqTypeToStr);
    if (m.find("write_home_timeline_service") != m.end()) {
        posS = m.find("write_home_timeline_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("write_home_timeline_service on %s", posS.c_str());
    serv_write_home_timeline_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_write_home_timeline_service", simgrid::s4u::Host::by_name(posS), [serv_write_home_timeline_service] { serv_write_home_timeline_service->run(); });


    // create ETM for service social_graph_service
    std::vector<std::string> v_serv_social_graph_service = std::vector<std::string>();
    v_serv_social_graph_service.push_back("social_graph_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_social_graph_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("social_graph_service",v_serv_social_graph_service);
    serv_social_graph_service->setBootDuration(0);
    serv_social_graph_service->setDataSizeRatio(1);
    serv_social_graph_service->setParallelTasksPerInst(50);
    serv_social_graph_service->setOutputFunction(return_social_graph_service);
    serv_social_graph_service->setProcessRatioFunc(pr_social_graph_service);
    serv_social_graph_service->setReqNames(reqTypeToStr);
    if (m.find("social_graph_service") != m.end()) {
        posS = m.find("social_graph_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("social_graph_service on %s", posS.c_str());
    serv_social_graph_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_social_graph_service", simgrid::s4u::Host::by_name(posS), [serv_social_graph_service] { serv_social_graph_service->run(); });


    // create ETM for service unique_id_service
    std::vector<std::string> v_serv_unique_id_service = std::vector<std::string>();
    v_serv_unique_id_service.push_back("unique_id_service");
    std::shared_ptr<simgrid::s4u::ElasticTaskManager> serv_unique_id_service = std::make_shared<simgrid::s4u::ElasticTaskManager>("unique_id_service",v_serv_unique_id_service);
    serv_unique_id_service->setBootDuration(0);
    serv_unique_id_service->setDataSizeRatio(1);
    serv_unique_id_service->setParallelTasksPerInst(50);
    serv_unique_id_service->setOutputFunction(return_unique_id_service);
    serv_unique_id_service->setProcessRatioFunc(pr_unique_id_service);
    serv_unique_id_service->setReqNames(reqTypeToStr);
    if (m.find("unique_id_service") != m.end()) {
        posS = m.find("unique_id_service")->second;
    }else{
        posS = m.find("default")->second;
    }
    XBT_INFO("unique_id_service on %s", posS.c_str());
    serv_unique_id_service->addHost(simgrid::s4u::Host::by_name(posS));
    simgrid::s4u::Actor::create("etm_unique_id_service", simgrid::s4u::Host::by_name(posS), [serv_unique_id_service] { serv_unique_id_service->run(); });


  /* ADD DATASOURCES MANUALLY HERE, SET THE END TIMER AS YOU WISH, AND LAUNCH YOUR SIMULATOR*/
  DataSourceFixedInterval* dsf = new DataSourceFixedInterval("nginx_web_server",RequestType::COMPOSE, 31,100);
  simgrid::s4u::ActorPtr dataS = simgrid::s4u::Actor::create("snd", simgrid::s4u::Host::by_name("cb1-100"), [&]{dsf->run();});

  // kill policies and ETMs
  simgrid::s4u::this_actor::sleep_for(150); /*set it according to your needs*/
  XBT_INFO("Done. Killing policies and etms");
      dataS->kill();
    serv_nginx_web_server->kill();
    serv_media_service->kill();
    serv_compose_post_service->kill();
    serv_user_service->kill();
    serv_text_service->kill();
    serv_url_shorten_service->kill();
    serv_user_mention_service->kill();
    serv_post_storage_service->kill();
    serv_user_timeline_service->kill();
    serv_write_home_timeline_service->kill();
    serv_social_graph_service->kill();
    serv_unique_id_service->kill();
}
int main(int argc, char* argv[]) {
	simgrid::s4u::Engine* e = new simgrid::s4u::Engine(&argc, argv);

      // create a map from the file
      std::string fname = argv[2];
      std::ifstream input(fname);
      std::map<std::string, std::string> pos;
      for (std::string token1, token2; input >> token1 >> token2;) {
            pos[token1] = token2;
      }

	e->load_platform(argv[1]);
	simgrid::s4u::Actor::create("main", simgrid::s4u::Host::by_name("cb1-200"), [&]{run(pos);});
	e->run();
	return 0;
}
