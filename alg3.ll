; ModuleID = './test/dfg/src/alg3.bc'
source_filename = "self_tests/src_huawei/alg3.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @_Z9alg3_funcPtS_jj(ptr nocapture noundef readonly %0, ptr nocapture noundef writeonly %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #0 {
  %5 = lshr i32 %2, 1
  %6 = lshr i32 %3, 1
  %7 = mul i32 %6, %5
  %8 = shl i32 %7, 4
  %9 = tail call noalias ptr @malloc(i32 noundef %8) #4
  %10 = add nuw i32 %5, 8
  %11 = add nuw i32 %6, 8
  %12 = mul i32 %11, %10
  %13 = shl i32 %12, 4
  %14 = tail call noalias ptr @malloc(i32 noundef %13) #4
  %15 = mul i32 %3, %2
  %16 = lshr i32 %15, 2
  %17 = icmp ult i32 %15, 4
  br i1 %17, label %22, label %18

18:                                               ; preds = %4
  %19 = shl i32 %7, 1
  %20 = mul i32 %7, 3
  %21 = tail call i32 @llvm.umax.i32(i32 %16, i32 1)
  br label %26

22:                                               ; preds = %26, %4
  %23 = shl i32 %6, 2
  %24 = mul i32 %23, %5
  %25 = icmp eq i32 %24, 0
  br i1 %25, label %68, label %71

26:                                               ; preds = %18, %26
  %27 = phi i32 [ 0, %18 ], [ %66, %26 ]
  %28 = phi i32 [ undef, %18 ], [ %34, %26 ]
  %29 = urem i32 %27, %5
  %30 = icmp eq i32 %29, 0
  %31 = icmp ne i32 %27, 0
  %32 = and i1 %31, %30
  %33 = zext i1 %32 to i32
  %34 = add nsw i32 %28, %33
  %35 = shl nsw i32 %34, 1
  %36 = mul i32 %35, %2
  %37 = shl nuw nsw i32 %29, 1
  %38 = add i32 %36, %37
  %39 = getelementptr inbounds i16, ptr %0, i32 %38
  %40 = load i16, ptr %39, align 2, !tbaa !6
  %41 = zext i16 %40 to i32
  %42 = mul i32 %34, %2
  %43 = lshr i32 %42, 1
  %44 = add nuw i32 %43, %29
  %45 = getelementptr inbounds i32, ptr %9, i32 %44
  store i32 %41, ptr %45, align 4, !tbaa !10
  %46 = or i32 %38, 1
  %47 = getelementptr inbounds i16, ptr %0, i32 %46
  %48 = load i16, ptr %47, align 2, !tbaa !6
  %49 = zext i16 %48 to i32
  %50 = add i32 %44, %7
  %51 = getelementptr inbounds i32, ptr %9, i32 %50
  store i32 %49, ptr %51, align 4, !tbaa !10
  %52 = or i32 %35, 1
  %53 = mul i32 %52, %2
  %54 = add i32 %53, %37
  %55 = getelementptr inbounds i16, ptr %0, i32 %54
  %56 = load i16, ptr %55, align 2, !tbaa !6
  %57 = zext i16 %56 to i32
  %58 = add i32 %44, %19
  %59 = getelementptr inbounds i32, ptr %9, i32 %58
  store i32 %57, ptr %59, align 4, !tbaa !10
  %60 = add i32 %54, 1
  %61 = getelementptr inbounds i16, ptr %0, i32 %60
  %62 = load i16, ptr %61, align 2, !tbaa !6
  %63 = zext i16 %62 to i32
  %64 = add i32 %44, %20
  %65 = getelementptr inbounds i32, ptr %9, i32 %64
  store i32 %63, ptr %65, align 4, !tbaa !10
  %66 = add nuw nsw i32 %27, 1
  %67 = icmp eq i32 %66, %21
  br i1 %67, label %22, label %26, !llvm.loop !12

68:                                               ; preds = %71, %22
  %69 = shl i32 %6, 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %135, label %106

71:                                               ; preds = %22, %71
  %72 = phi i32 [ %100, %71 ], [ 0, %22 ]
  %73 = phi i32 [ %80, %71 ], [ 0, %22 ]
  %74 = phi i32 [ %85, %71 ], [ 0, %22 ]
  %75 = urem i32 %72, %7
  %76 = icmp eq i32 %75, 0
  %77 = icmp ne i32 %72, 0
  %78 = and i1 %77, %76
  %79 = zext i1 %78 to i32
  %80 = add nuw nsw i32 %73, %79
  %81 = urem i32 %72, %5
  %82 = icmp eq i32 %81, 0
  %83 = and i1 %77, %82
  %84 = zext i1 %83 to i32
  %85 = add nuw nsw i32 %74, %84
  %86 = mul i32 %85, %2
  %87 = lshr i32 %86, 1
  %88 = mul i32 %7, %80
  %89 = add i32 %88, %81
  %90 = add i32 %89, %87
  %91 = getelementptr inbounds i32, ptr %9, i32 %90
  %92 = load i32, ptr %91, align 4, !tbaa !10
  %93 = add nuw nsw i32 %85, 4
  %94 = mul i32 %80, %11
  %95 = add i32 %93, %94
  %96 = mul i32 %95, %10
  %97 = add nuw i32 %81, 4
  %98 = add i32 %97, %96
  %99 = getelementptr inbounds i32, ptr %14, i32 %98
  store i32 %92, ptr %99, align 4, !tbaa !10
  %100 = add nuw nsw i32 %72, 1
  %101 = icmp eq i32 %100, %24
  br i1 %101, label %68, label %71, !llvm.loop !15

102:                                              ; preds = %106
  br i1 %70, label %135, label %103

103:                                              ; preds = %102
  %104 = add nsw i32 %5, -1
  %105 = add nuw i32 %5, 4
  br label %140

106:                                              ; preds = %68, %106
  %107 = phi i32 [ %133, %106 ], [ 0, %68 ]
  %108 = phi i32 [ %115, %106 ], [ 0, %68 ]
  %109 = phi i32 [ %120, %106 ], [ 4, %68 ]
  %110 = urem i32 %107, %23
  %111 = icmp eq i32 %110, 0
  %112 = icmp ne i32 %107, 0
  %113 = and i1 %112, %111
  %114 = zext i1 %113 to i32
  %115 = add nuw nsw i32 %108, %114
  %116 = and i32 %107, 3
  %117 = icmp eq i32 %116, 0
  %118 = and i1 %112, %117
  %119 = zext i1 %118 to i32
  %120 = add nuw nsw i32 %109, %119
  %121 = add nsw i32 %120, -4
  %122 = mul i32 %121, %2
  %123 = lshr i32 %122, 1
  %124 = mul i32 %7, %115
  %125 = add i32 %124, %123
  %126 = getelementptr inbounds i32, ptr %9, i32 %125
  %127 = load i32, ptr %126, align 4, !tbaa !10
  %128 = mul i32 %115, %11
  %129 = add i32 %128, %120
  %130 = mul i32 %129, %10
  %131 = add i32 %130, %116
  %132 = getelementptr inbounds i32, ptr %14, i32 %131
  store i32 %127, ptr %132, align 4, !tbaa !10
  %133 = add nuw nsw i32 %107, 1
  %134 = icmp eq i32 %133, %69
  br i1 %134, label %102, label %106, !llvm.loop !16

135:                                              ; preds = %140, %68, %102
  %136 = shl i32 %10, 4
  %137 = icmp eq i32 %136, 0
  br i1 %137, label %202, label %138

138:                                              ; preds = %135
  %139 = shl i32 %10, 2
  br label %177

140:                                              ; preds = %103, %140
  %141 = phi i32 [ 0, %103 ], [ %169, %140 ]
  %142 = phi i32 [ 0, %103 ], [ %149, %140 ]
  %143 = phi i32 [ 4, %103 ], [ %154, %140 ]
  %144 = urem i32 %141, %23
  %145 = icmp eq i32 %144, 0
  %146 = icmp ne i32 %141, 0
  %147 = and i1 %146, %145
  %148 = zext i1 %147 to i32
  %149 = add nuw nsw i32 %142, %148
  %150 = and i32 %141, 3
  %151 = icmp eq i32 %150, 0
  %152 = and i1 %146, %151
  %153 = zext i1 %152 to i32
  %154 = add nuw nsw i32 %143, %153
  %155 = add nsw i32 %154, -4
  %156 = mul i32 %155, %2
  %157 = lshr i32 %156, 1
  %158 = mul i32 %7, %149
  %159 = add i32 %104, %157
  %160 = add i32 %159, %158
  %161 = getelementptr inbounds i32, ptr %9, i32 %160
  %162 = load i32, ptr %161, align 4, !tbaa !10
  %163 = mul i32 %149, %11
  %164 = add i32 %163, %154
  %165 = mul i32 %164, %10
  %166 = add i32 %105, %150
  %167 = add i32 %166, %165
  %168 = getelementptr inbounds i32, ptr %14, i32 %167
  store i32 %162, ptr %168, align 4, !tbaa !10
  %169 = add nuw nsw i32 %141, 1
  %170 = icmp eq i32 %169, %69
  br i1 %170, label %135, label %140, !llvm.loop !17

171:                                              ; preds = %177
  br i1 %137, label %202, label %172

172:                                              ; preds = %171
  %173 = add nuw i32 %6, 4
  %174 = shl i32 %10, 2
  %175 = add nuw i32 %6, 3
  %176 = mul i32 %175, %10
  br label %203

177:                                              ; preds = %138, %177
  %178 = phi i32 [ 0, %138 ], [ %200, %177 ]
  %179 = phi i32 [ 0, %138 ], [ %186, %177 ]
  %180 = phi i32 [ 0, %138 ], [ %191, %177 ]
  %181 = urem i32 %178, %139
  %182 = icmp eq i32 %181, 0
  %183 = icmp ne i32 %178, 0
  %184 = and i1 %183, %182
  %185 = zext i1 %184 to i32
  %186 = add nuw nsw i32 %179, %185
  %187 = urem i32 %178, %10
  %188 = icmp eq i32 %187, 0
  %189 = and i1 %183, %188
  %190 = zext i1 %189 to i32
  %191 = add nuw nsw i32 %180, %190
  %192 = mul i32 %12, %186
  %193 = add i32 %192, %187
  %194 = add i32 %193, %139
  %195 = getelementptr inbounds i32, ptr %9, i32 %194
  %196 = load i32, ptr %195, align 4, !tbaa !10
  %197 = mul i32 %191, %10
  %198 = add i32 %193, %197
  %199 = getelementptr inbounds i32, ptr %14, i32 %198
  store i32 %196, ptr %199, align 4, !tbaa !10
  %200 = add nuw nsw i32 %178, 1
  %201 = icmp eq i32 %200, %136
  br i1 %201, label %171, label %177, !llvm.loop !18

202:                                              ; preds = %203, %135, %171
  br i1 %25, label %228, label %233

203:                                              ; preds = %172, %203
  %204 = phi i32 [ 0, %172 ], [ %226, %203 ]
  %205 = phi i32 [ 0, %172 ], [ %212, %203 ]
  %206 = phi i32 [ %173, %172 ], [ %217, %203 ]
  %207 = urem i32 %204, %174
  %208 = icmp eq i32 %207, 0
  %209 = icmp ne i32 %204, 0
  %210 = and i1 %209, %208
  %211 = zext i1 %210 to i32
  %212 = add nuw nsw i32 %205, %211
  %213 = urem i32 %204, %10
  %214 = icmp eq i32 %213, 0
  %215 = and i1 %209, %214
  %216 = zext i1 %215 to i32
  %217 = add nsw i32 %206, %216
  %218 = mul i32 %12, %212
  %219 = add i32 %218, %213
  %220 = add i32 %219, %176
  %221 = getelementptr inbounds i32, ptr %9, i32 %220
  %222 = load i32, ptr %221, align 4, !tbaa !10
  %223 = mul i32 %217, %10
  %224 = add i32 %219, %223
  %225 = getelementptr inbounds i32, ptr %14, i32 %224
  store i32 %222, ptr %225, align 4, !tbaa !10
  %226 = add nuw nsw i32 %204, 1
  %227 = icmp eq i32 %226, %136
  br i1 %227, label %202, label %203, !llvm.loop !19

228:                                              ; preds = %233, %202
  br i1 %17, label %266, label %229

229:                                              ; preds = %228
  %230 = shl i32 %7, 1
  %231 = mul i32 %7, 3
  %232 = tail call i32 @llvm.umax.i32(i32 %16, i32 1)
  br label %267

233:                                              ; preds = %202, %233
  %234 = phi i32 [ %264, %233 ], [ 0, %202 ]
  %235 = phi i32 [ %242, %233 ], [ 0, %202 ]
  %236 = phi i32 [ %247, %233 ], [ 4, %202 ]
  %237 = urem i32 %234, %7
  %238 = icmp eq i32 %237, 0
  %239 = icmp ne i32 %234, 0
  %240 = and i1 %239, %238
  %241 = zext i1 %240 to i32
  %242 = add nuw nsw i32 %235, %241
  %243 = urem i32 %234, %5
  %244 = icmp eq i32 %243, 0
  %245 = and i1 %239, %244
  %246 = zext i1 %245 to i32
  %247 = add nuw nsw i32 %236, %246
  %248 = add nsw i32 %247, -4
  %249 = mul i32 %242, %11
  %250 = add i32 %249, %247
  %251 = mul i32 %250, %10
  %252 = add nuw i32 %243, 1
  %253 = add i32 %252, %251
  %254 = getelementptr inbounds i32, ptr %14, i32 %253
  %255 = load i32, ptr %254, align 4, !tbaa !10
  %256 = and i32 %255, 255
  %257 = mul i32 %248, %2
  %258 = lshr i32 %257, 1
  %259 = add nsw i32 %243, -4
  %260 = mul i32 %7, %242
  %261 = add i32 %259, %260
  %262 = add i32 %261, %258
  %263 = getelementptr inbounds i32, ptr %9, i32 %262
  store i32 %256, ptr %263, align 4, !tbaa !10
  %264 = add nuw nsw i32 %234, 1
  %265 = icmp eq i32 %264, %24
  br i1 %265, label %228, label %233, !llvm.loop !20

266:                                              ; preds = %267, %228
  tail call void @free(ptr noundef %9) #5
  tail call void @free(ptr noundef %14) #5
  ret void

267:                                              ; preds = %229, %267
  %268 = phi i32 [ 0, %229 ], [ %307, %267 ]
  %269 = phi i32 [ 0, %229 ], [ %275, %267 ]
  %270 = urem i32 %268, %5
  %271 = icmp eq i32 %270, 0
  %272 = icmp ne i32 %268, 0
  %273 = and i1 %272, %271
  %274 = zext i1 %273 to i32
  %275 = add nuw nsw i32 %269, %274
  %276 = mul i32 %275, %2
  %277 = lshr i32 %276, 1
  %278 = add nuw i32 %277, %270
  %279 = getelementptr inbounds i32, ptr %9, i32 %278
  %280 = load i32, ptr %279, align 4, !tbaa !10
  %281 = trunc i32 %280 to i16
  %282 = shl nuw nsw i32 %275, 1
  %283 = mul i32 %282, %2
  %284 = shl nuw nsw i32 %270, 1
  %285 = add i32 %283, %284
  %286 = getelementptr inbounds i16, ptr %1, i32 %285
  store i16 %281, ptr %286, align 2, !tbaa !6
  %287 = add i32 %278, %7
  %288 = getelementptr inbounds i32, ptr %9, i32 %287
  %289 = load i32, ptr %288, align 4, !tbaa !10
  %290 = trunc i32 %289 to i16
  %291 = or i32 %285, 1
  %292 = getelementptr inbounds i16, ptr %1, i32 %291
  store i16 %290, ptr %292, align 2, !tbaa !6
  %293 = add i32 %278, %230
  %294 = getelementptr inbounds i32, ptr %9, i32 %293
  %295 = load i32, ptr %294, align 4, !tbaa !10
  %296 = trunc i32 %295 to i16
  %297 = or i32 %282, 1
  %298 = mul i32 %297, %2
  %299 = add i32 %298, %284
  %300 = getelementptr inbounds i16, ptr %1, i32 %299
  store i16 %296, ptr %300, align 2, !tbaa !6
  %301 = add i32 %278, %231
  %302 = getelementptr inbounds i32, ptr %9, i32 %301
  %303 = load i32, ptr %302, align 4, !tbaa !10
  %304 = trunc i32 %303 to i16
  %305 = add i32 %299, 1
  %306 = getelementptr inbounds i16, ptr %1, i32 %305
  store i16 %304, ptr %306, align 2, !tbaa !6
  %307 = add nuw nsw i32 %268, 1
  %308 = icmp eq i32 %307, %232
  br i1 %308, label %266, label %267, !llvm.loop !21
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i32 noundef) local_unnamed_addr #1

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr nocapture noundef) local_unnamed_addr #2

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umax.i32(i32, i32) #3

attributes #0 = { mustprogress nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #3 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #4 = { nounwind allocsize(0) }
attributes #5 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!"Ubuntu clang version 16.0.6 (++20231112100421+7cbf1a259152-1~exp1~20231112100514.107)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"short", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = !{!11, !11, i64 0}
!11 = !{!"int", !8, i64 0}
!12 = distinct !{!12, !13, !14}
!13 = !{!"llvm.loop.mustprogress"}
!14 = !{!"llvm.loop.unroll.disable"}
!15 = distinct !{!15, !13, !14}
!16 = distinct !{!16, !13, !14}
!17 = distinct !{!17, !13, !14}
!18 = distinct !{!18, !13, !14}
!19 = distinct !{!19, !13, !14}
!20 = distinct !{!20, !13, !14}
!21 = distinct !{!21, !13, !14}
