#include <SketchUpAPI/common.h>
#include <SketchUpAPI/geometry.h>
#include <SketchUpAPI/initialize.h>
#include <SketchUpAPI/unicodestring.h>
#include <SketchUpAPI/model/model.h>
#include <SketchUpAPI/model/entities.h>
#include <SketchUpAPI/model/face.h>
#include <SketchUpAPI/model/edge.h>
#include <SketchUpAPI/model/vertex.h>
#include <vector>
#include <iostream>

int main_ori() {
  // Always initialize the API before using it
  SUInitialize();

  // Load the model from a file
  SUModelRef model = SU_INVALID;
  SUModelLoadStatus status;
  SUResult res = SUModelCreateFromFileWithStatus(&model, "/Users/shangqisen/Downloads/3d/A_Kaiwharawhara.skp", &status);

  // It's best to always check the return code from each SU function call.
  // Only showing this check once to keep this example short.
  if (res != SU_ERROR_NONE) {
    std::cout << "Failed creating model from a file" << std::endl;
    return 1;
  }

  if (status == SUModelLoadStatus_Success_MoreRecent) {
    std::cout
        << "This model was created in a more recent SketchUp version than that of the SDK. "
           "It contains data which will not be read. Saving the model over the original file may "
           "lead to permanent data loss."
        << std::endl;
  }

  // Get the entity container of the model.
  SUEntitiesRef entities = SU_INVALID;
  SUModelGetEntities(model, &entities);

  // Get all the faces from the entities object
  size_t faceCount = 0;
  SUEntitiesGetNumFaces(entities, &faceCount);
  std::cout << "Number of faces: " << faceCount << std::endl;
  if (faceCount > 0) {
    std::vector<SUFaceRef> faces(faceCount);
    SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);
    //SUVertexSetPosition(SUVertexRef vertex, <#const struct SUPoint3D *position#>)
    // Get all the edges in this face
    for (size_t i = 0; i < faceCount; i++) {
      size_t edgeCount = 0;
      SUFaceGetNumEdges(faces[i], &edgeCount);
      if (edgeCount > 0) {
        std::vector<SUEdgeRef> edges(edgeCount);
        SUFaceGetEdges(faces[i], edgeCount, &edges[0], &edgeCount);
        // Get the vertex positions for each edge
        for (size_t j = 0; j < edgeCount; j++) {
          SUVertexRef startVertex = SU_INVALID;
          SUVertexRef endVertex = SU_INVALID;
          SUEdgeGetStartVertex(edges[j], &startVertex);
          SUEdgeGetEndVertex(edges[j], &endVertex);
          SUPoint3D start;
          SUPoint3D end;
          SUVertexGetPosition(startVertex, &start);
          SUVertexGetPosition(endVertex, &end);
            
            //SUEntitiesTransform(SUEntitiesRef entities, <#size_t len#>, SUEntityRef *elements, <#const struct SUTransformation *trans#>)
            if(start.x>10000000)
            {
                //std::cout<<"before X"<<" "<<start.x<<std::endl;
                start.x = start.x / 10000000;
                SUVertexSetPosition(startVertex, &start);
                SUPoint3D start_after;
                SUVertexGetPosition(startVertex, &start_after);
                //std::cout<<"after X"<<" "<<start_after.x<<std::endl;
                //int a = 0;
            }
            
            if(start.y>10000000)
            {
                //std::cout<<"before Y"<<" "<<start.y<<std::endl;
                start.y = start.y / 10000000;
                SUVertexSetPosition(startVertex, &start);
                SUPoint3D start_after;
                SUVertexGetPosition(startVertex, &start_after);
                //std::cout<<"after Y"<<" "<<start_after.y<<std::endl;
                //int a = 0;
            }
            
            if(start.z>10000000)
            {
                //std::cout<<"before Z"<<" "<<start.z<<std::endl;
                start.z = start.z / 10000000;
                SUVertexSetPosition(startVertex, &start);
                SUPoint3D start_after;
                SUVertexGetPosition(startVertex, &start_after);
                //std::cout<<"after Z"<<" "<<start_after.z<<std::endl;
                //int a = 0;
            }

          // Now do something with the point data
            
            SUEdgeGetStartVertex(edges[j], &startVertex);
            SUEdgeGetEndVertex(edges[j], &endVertex);
            
        }
      }
    }
  }

  // Get model name
  SUStringRef name = SU_INVALID;
  SUStringCreate(&name);
  SUModelGetName(model, &name);
  size_t name_length = 0;
  SUStringGetUTF8Length(name, &name_length);
  char* name_utf8 = new char[name_length + 1];
  SUStringGetUTF8(name, name_length + 1, name_utf8, &name_length);
  // Now we have the name in a form we can use
  SUStringRelease(&name);
  delete[] name_utf8;

  // Must release the model or there will be memory leaks
  SUResult result = SUModelRelease(&model);

  if (result != SU_ERROR_NONE) {
    std::cout << "Reading SketchUp model: Failed" << std::endl;
  } else {
    std::cout << "Reading SketchUp model: Success" << std::endl;
  }
  // Always terminate the API when done using it
  SUTerminate();

  return 0;
}

std::vector<double> GetMinXY(SUEntitiesRef entities){
    std::vector<double> res;
    double x = 0;
    double y = 0;
    size_t faceCount = 0;
    SUEntitiesGetNumFaces(entities, &faceCount);
    if (faceCount > 0) {
        std::vector<SUFaceRef> faces(faceCount);
        SUEntitiesGetFaces(entities, faceCount, &faces[0], &faceCount);
        //SUVertexSetPosition(SUVertexRef vertex, <#const struct SUPoint3D *position#>)
        // Get all the edges in this face
        for (size_t i = 0; i < faceCount; i++) {
            size_t edgeCount = 0;
            SUFaceGetNumEdges(faces[i], &edgeCount);
            if (edgeCount > 0) {
                std::vector<SUEdgeRef> edges(edgeCount);
                SUFaceGetEdges(faces[i], edgeCount, &edges[0], &edgeCount);
                // Get the vertex positions for each edge
                for (size_t j = 0; j < edgeCount; j++) {
                    SUVertexRef startVertex = SU_INVALID;
                    SUVertexRef endVertex = SU_INVALID;
                    SUEdgeGetStartVertex(edges[j], &startVertex);
                    SUEdgeGetEndVertex(edges[j], &endVertex);
                    SUPoint3D start;
                    SUPoint3D end;
                    SUVertexGetPosition(startVertex, &start);
                    SUVertexGetPosition(endVertex, &end);
                    // Now do something with the point data
                    double temp_start_x, temp_start_y, temp_end_x, temp_end_y;
                    temp_start_x = start.x;
                    temp_start_y = start.y;
                    temp_end_x = end.x;
                    temp_end_y = end.y;
                    
                    if(temp_start_x < temp_end_x)
                        x = temp_start_x;
                    else
                        x = temp_end_x;
                    
                    if(temp_start_y < temp_end_y)
                        y = temp_start_y;
                    else
                        y = temp_end_y;
                    
                }
            }
        }
    }
    res.push_back(x);
    res.push_back(y);
    return res;
}

std::vector<SUEntityRef> get_edges(SUEntitiesRef entities)
{
    size_t amount{ 0 };
    std::vector<SUEntityRef> ents{};
    SUEntitiesGetNumEdges(entities, false, &amount);
    size_t count{ 0 };
    std::vector<SUEdgeRef> edges(amount);
    SUEntitiesGetEdges(entities, false, amount, &edges[0], &count);
    for (auto& edge : edges) {
        ents.push_back(SUEdgeToEntity(edge));
    }
    return ents;
}

std::vector<SUEntityRef> get_faces(SUEntitiesRef entities)
{
    size_t amount{ 0 };
    std::vector<SUEntityRef> ents{};
    SUEntitiesGetNumFaces(entities, &amount);
    size_t count{ 0 };
    std::vector<SUFaceRef> faces(amount);
    SUEntitiesGetFaces(entities, amount, &faces[0], &count);
    for (auto& face : faces) {
        ents.push_back(SUFaceToEntity(face));
    }
    return ents;
}

int main(){
    SUInitialize();
    
    SUModelRef model = SU_INVALID;
    SUModelLoadStatus status;
    SUResult res = SUModelCreateFromFileWithStatus(&model, "/Users/shangqisen/Downloads/3d/pipitea/D_Pipitea_South.skp", &status);
    //
    if (res != SU_ERROR_NONE) {
      std::cout << "Failed creating model from a file" << std::endl;
      return 1;
    }

    if (status == SUModelLoadStatus_Success_MoreRecent) {
      std::cout
          << "This model was created in a more recent SketchUp version than that of the SDK. "
             "It contains data which will not be read. Saving the model over the original file may "
             "lead to permanent data loss."
          << std::endl;
    }
    //
    SUEntitiesRef entities = SU_INVALID;
    SUModelGetEntities(model, &entities);
    std::vector<double> min = GetMinXY(entities);
    double min_x = min[0];
    double min_y = min[1];
    /**################################**/
    // {1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -60000000.0, -200000000.0, 0.0, 1.0}
    SUTransformation tr{1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -min_x, -min_y, 0.0, 1.0};
    //std::vector<SUEntityRef> edges{ get_edges(entities) };
    //res = SUEntitiesTransform(entities, edges.size(), &edges[0], &tr);
    std::vector<SUEntityRef> faces{ get_faces(entities) };
    size_t face_count = faces.size();
    res = SUEntitiesTransform(entities, face_count, &faces[0], &tr);
    res = SUModelSaveToFile(model, "/Users/shangqisen/Downloads/3d/new_model.skp");
    assert(res == SU_ERROR_NONE);
    // std::cout << sketchup_error_string(res, __FILE__, __LINE__) << "\n";
    // Must release the model or there will be memory leaks
    SUModelRelease(&model);
    // Always terminate the API when done using it
    SUTerminate();
    /**################################**/
    return 0;
    
}
