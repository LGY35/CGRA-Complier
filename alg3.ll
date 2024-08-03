; ModuleID = './test/dfg/src/alg3.bc'
source_filename = "self_tests/src_huawei/alg3.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable
define dso_local noundef zeroext i8 @_Z11alg3_func_1Pii(ptr nocapture noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = add nsw i32 %1, -1
  %4 = mul nsw i32 %3, %1
  %5 = sdiv i32 %4, 2
  %6 = icmp sgt i32 %4, 1
  br i1 %6, label %10, label %7

7:                                                ; preds = %25, %2
  %8 = and i32 %1, 1
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %33, label %28

10:                                               ; preds = %2, %25
  %11 = phi i32 [ %26, %25 ], [ 0, %2 ]
  %12 = srem i32 %11, %3
  %13 = sdiv i32 %11, %3
  %14 = sub nsw i32 %3, %13
  %15 = icmp slt i32 %12, %14
  br i1 %15, label %16, label %25

16:                                               ; preds = %10
  %17 = getelementptr inbounds i32, ptr %0, i32 %12
  %18 = load i32, ptr %17, align 4, !tbaa !6
  %19 = add nuw nsw i32 %12, 1
  %20 = getelementptr inbounds i32, ptr %0, i32 %19
  %21 = load i32, ptr %20, align 4, !tbaa !6
  %22 = icmp sgt i32 %18, %21
  br i1 %22, label %23, label %25

23:                                               ; preds = %16
  store i32 %21, ptr %17, align 4, !tbaa !6
  %24 = and i32 %18, 255
  store i32 %24, ptr %20, align 4, !tbaa !6
  br label %25

25:                                               ; preds = %10, %23, %16
  %26 = add nuw nsw i32 %11, 1
  %27 = icmp eq i32 %26, %5
  br i1 %27, label %7, label %10, !llvm.loop !10

28:                                               ; preds = %7
  %29 = add nsw i32 %1, 1
  %30 = sdiv i32 %29, 2
  %31 = getelementptr inbounds i32, ptr %0, i32 %30
  %32 = load i32, ptr %31, align 4, !tbaa !6
  br label %42

33:                                               ; preds = %7
  %34 = sdiv i32 %1, 2
  %35 = getelementptr inbounds i32, ptr %0, i32 %34
  %36 = load i32, ptr %35, align 4, !tbaa !6
  %37 = add nsw i32 %34, 1
  %38 = getelementptr inbounds i32, ptr %0, i32 %37
  %39 = load i32, ptr %38, align 4, !tbaa !6
  %40 = add nsw i32 %39, %36
  %41 = sdiv i32 %40, 2
  br label %42

42:                                               ; preds = %33, %28
  %43 = phi i32 [ %32, %28 ], [ %41, %33 ]
  %44 = trunc i32 %43 to i8
  ret i8 %44
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @_Z9alg3_funcPjS_jj(ptr nocapture noundef readonly %0, ptr nocapture noundef writeonly %1, i32 noundef %2, i32 noundef %3) local_unnamed_addr #2 {
  %5 = alloca [81 x i32], align 4
  %6 = lshr i32 %2, 1
  %7 = lshr i32 %3, 1
  %8 = mul i32 %7, %6
  %9 = shl i32 %8, 4
  %10 = tail call noalias ptr @malloc(i32 noundef %9) #7
  %11 = add nuw i32 %6, 8
  %12 = add nuw i32 %7, 8
  %13 = mul i32 %12, %11
  %14 = shl i32 %13, 4
  %15 = tail call noalias ptr @malloc(i32 noundef %14) #7
  %16 = mul i32 %3, %2
  %17 = lshr i32 %16, 2
  %18 = icmp ult i32 %16, 4
  br i1 %18, label %23, label %19

19:                                               ; preds = %4
  %20 = shl i32 %8, 1
  %21 = mul i32 %8, 3
  %22 = tail call i32 @llvm.umax.i32(i32 %17, i32 1)
  br label %27

23:                                               ; preds = %27, %4
  %24 = shl i32 %7, 2
  %25 = mul i32 %24, %6
  %26 = icmp eq i32 %25, 0
  br i1 %26, label %65, label %68

27:                                               ; preds = %19, %27
  %28 = phi i32 [ 0, %19 ], [ %63, %27 ]
  %29 = phi i32 [ undef, %19 ], [ %35, %27 ]
  %30 = urem i32 %28, %6
  %31 = icmp eq i32 %30, 0
  %32 = icmp ne i32 %28, 0
  %33 = and i1 %32, %31
  %34 = zext i1 %33 to i32
  %35 = add i32 %29, %34
  %36 = shl i32 %35, 1
  %37 = mul i32 %36, %2
  %38 = shl nuw i32 %30, 1
  %39 = add i32 %37, %38
  %40 = getelementptr inbounds i32, ptr %0, i32 %39
  %41 = load i32, ptr %40, align 4, !tbaa !6
  %42 = mul i32 %35, %2
  %43 = lshr i32 %42, 1
  %44 = add nuw i32 %43, %30
  %45 = getelementptr inbounds i32, ptr %10, i32 %44
  store i32 %41, ptr %45, align 4, !tbaa !6
  %46 = or i32 %39, 1
  %47 = getelementptr inbounds i32, ptr %0, i32 %46
  %48 = load i32, ptr %47, align 4, !tbaa !6
  %49 = add i32 %44, %8
  %50 = getelementptr inbounds i32, ptr %10, i32 %49
  store i32 %48, ptr %50, align 4, !tbaa !6
  %51 = or i32 %36, 1
  %52 = mul i32 %51, %2
  %53 = add i32 %52, %38
  %54 = getelementptr inbounds i32, ptr %0, i32 %53
  %55 = load i32, ptr %54, align 4, !tbaa !6
  %56 = add i32 %44, %20
  %57 = getelementptr inbounds i32, ptr %10, i32 %56
  store i32 %55, ptr %57, align 4, !tbaa !6
  %58 = add i32 %53, 1
  %59 = getelementptr inbounds i32, ptr %0, i32 %58
  %60 = load i32, ptr %59, align 4, !tbaa !6
  %61 = add i32 %44, %21
  %62 = getelementptr inbounds i32, ptr %10, i32 %61
  store i32 %60, ptr %62, align 4, !tbaa !6
  %63 = add nuw nsw i32 %28, 1
  %64 = icmp eq i32 %63, %22
  br i1 %64, label %23, label %27, !llvm.loop !13

65:                                               ; preds = %68, %23
  %66 = shl i32 %7, 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %114, label %94

68:                                               ; preds = %23, %68
  %69 = phi i32 [ %88, %68 ], [ 0, %23 ]
  %70 = udiv i32 %69, %8
  %71 = udiv i32 %69, %6
  %72 = urem i32 %71, %7
  %73 = urem i32 %69, %6
  %74 = mul i32 %72, %2
  %75 = lshr i32 %74, 1
  %76 = mul i32 %8, %70
  %77 = add i32 %73, %76
  %78 = add i32 %77, %75
  %79 = getelementptr inbounds i32, ptr %10, i32 %78
  %80 = load i32, ptr %79, align 4, !tbaa !6
  %81 = add nuw i32 %72, 4
  %82 = mul i32 %70, %12
  %83 = add i32 %81, %82
  %84 = mul i32 %83, %11
  %85 = add nuw i32 %73, 4
  %86 = add i32 %85, %84
  %87 = getelementptr inbounds i32, ptr %15, i32 %86
  store i32 %80, ptr %87, align 4, !tbaa !6
  %88 = add nuw nsw i32 %69, 1
  %89 = icmp eq i32 %88, %25
  br i1 %89, label %65, label %68, !llvm.loop !14

90:                                               ; preds = %94
  br i1 %67, label %114, label %91

91:                                               ; preds = %90
  %92 = add nsw i32 %6, -1
  %93 = add nuw i32 %6, 4
  br label %119

94:                                               ; preds = %65, %94
  %95 = phi i32 [ %112, %94 ], [ 0, %65 ]
  %96 = udiv i32 %95, %7
  %97 = lshr i32 %95, 2
  %98 = urem i32 %97, %7
  %99 = add nuw nsw i32 %98, 4
  %100 = and i32 %95, 3
  %101 = mul i32 %98, %2
  %102 = lshr i32 %101, 1
  %103 = mul i32 %8, %96
  %104 = add i32 %102, %103
  %105 = getelementptr inbounds i32, ptr %10, i32 %104
  %106 = load i32, ptr %105, align 4, !tbaa !6
  %107 = mul i32 %96, %12
  %108 = add i32 %99, %107
  %109 = mul i32 %108, %11
  %110 = add i32 %109, %100
  %111 = getelementptr inbounds i32, ptr %15, i32 %110
  store i32 %106, ptr %111, align 4, !tbaa !6
  %112 = add nuw nsw i32 %95, 1
  %113 = icmp eq i32 %112, %66
  br i1 %113, label %90, label %94, !llvm.loop !15

114:                                              ; preds = %119, %65, %90
  %115 = shl i32 %11, 4
  %116 = icmp eq i32 %115, 0
  br i1 %116, label %172, label %117

117:                                              ; preds = %114
  %118 = shl i32 %11, 2
  br label %147

119:                                              ; preds = %91, %119
  %120 = phi i32 [ 0, %91 ], [ %139, %119 ]
  %121 = udiv i32 %120, %7
  %122 = lshr i32 %120, 2
  %123 = urem i32 %122, %7
  %124 = add nuw nsw i32 %123, 4
  %125 = and i32 %120, 3
  %126 = mul i32 %123, %2
  %127 = lshr i32 %126, 1
  %128 = mul i32 %8, %121
  %129 = add i32 %92, %128
  %130 = add i32 %129, %127
  %131 = getelementptr inbounds i32, ptr %10, i32 %130
  %132 = load i32, ptr %131, align 4, !tbaa !6
  %133 = mul i32 %121, %12
  %134 = add i32 %124, %133
  %135 = mul i32 %134, %11
  %136 = add i32 %93, %125
  %137 = add i32 %136, %135
  %138 = getelementptr inbounds i32, ptr %15, i32 %137
  store i32 %132, ptr %138, align 4, !tbaa !6
  %139 = add nuw nsw i32 %120, 1
  %140 = icmp eq i32 %139, %66
  br i1 %140, label %114, label %119, !llvm.loop !16

141:                                              ; preds = %147
  br i1 %116, label %172, label %142

142:                                              ; preds = %141
  %143 = shl i32 %11, 2
  %144 = add nuw i32 %7, 4
  %145 = add nuw i32 %7, 3
  %146 = mul i32 %145, %11
  br label %176

147:                                              ; preds = %117, %147
  %148 = phi i32 [ 0, %117 ], [ %170, %147 ]
  %149 = phi i32 [ 0, %117 ], [ %156, %147 ]
  %150 = phi i32 [ 0, %117 ], [ %161, %147 ]
  %151 = urem i32 %148, %118
  %152 = icmp eq i32 %151, 0
  %153 = icmp ne i32 %148, 0
  %154 = and i1 %153, %152
  %155 = zext i1 %154 to i32
  %156 = add i32 %149, %155
  %157 = urem i32 %148, %11
  %158 = icmp eq i32 %157, 0
  %159 = and i1 %153, %158
  %160 = zext i1 %159 to i32
  %161 = add i32 %150, %160
  %162 = mul i32 %13, %156
  %163 = add i32 %162, %157
  %164 = add i32 %163, %118
  %165 = getelementptr inbounds i32, ptr %10, i32 %164
  %166 = load i32, ptr %165, align 4, !tbaa !6
  %167 = mul i32 %161, %11
  %168 = add i32 %163, %167
  %169 = getelementptr inbounds i32, ptr %15, i32 %168
  store i32 %166, ptr %169, align 4, !tbaa !6
  %170 = add nuw nsw i32 %148, 1
  %171 = icmp eq i32 %170, %115
  br i1 %171, label %141, label %147, !llvm.loop !17

172:                                              ; preds = %176, %114, %141
  %173 = phi i32 [ 0, %141 ], [ 0, %114 ], [ %178, %176 ]
  call void @llvm.lifetime.start.p0(i64 324, ptr nonnull %5) #8
  call void @llvm.memset.p0.i32(ptr noundef nonnull align 4 dereferenceable(324) %5, i8 0, i32 324, i1 false)
  br i1 %26, label %193, label %174

174:                                              ; preds = %172
  %175 = getelementptr inbounds i32, ptr %5, i32 41
  br label %198

176:                                              ; preds = %142, %176
  %177 = phi i32 [ 0, %142 ], [ %191, %176 ]
  %178 = udiv i32 %177, %143
  %179 = udiv i32 %177, %11
  %180 = and i32 %179, 3
  %181 = add i32 %144, %180
  %182 = urem i32 %177, %11
  %183 = mul i32 %13, %178
  %184 = add i32 %183, %182
  %185 = add i32 %184, %146
  %186 = getelementptr inbounds i32, ptr %10, i32 %185
  %187 = load i32, ptr %186, align 4, !tbaa !6
  %188 = mul i32 %181, %11
  %189 = add i32 %184, %188
  %190 = getelementptr inbounds i32, ptr %15, i32 %189
  store i32 %187, ptr %190, align 4, !tbaa !6
  %191 = add nuw nsw i32 %177, 1
  %192 = icmp eq i32 %191, %115
  br i1 %192, label %172, label %176, !llvm.loop !18

193:                                              ; preds = %230, %172
  br i1 %18, label %259, label %194

194:                                              ; preds = %193
  %195 = shl i32 %8, 1
  %196 = mul i32 %8, 3
  %197 = tail call i32 @llvm.umax.i32(i32 %17, i32 1)
  br label %260

198:                                              ; preds = %174, %230
  %199 = phi i32 [ 0, %174 ], [ %239, %230 ]
  %200 = phi i32 [ %173, %174 ], [ %206, %230 ]
  %201 = urem i32 %199, %8
  %202 = icmp eq i32 %201, 0
  %203 = icmp ne i32 %199, 0
  %204 = and i1 %203, %202
  %205 = zext i1 %204 to i32
  %206 = add i32 %200, %205
  %207 = udiv i32 %199, %6
  %208 = and i32 %207, 3
  %209 = urem i32 %199, %6
  %210 = mul i32 %206, %12
  %211 = add i32 %210, %208
  br label %241

212:                                              ; preds = %241, %227
  %213 = phi i32 [ %228, %227 ], [ 0, %241 ]
  %214 = urem i32 %213, 80
  %215 = udiv i32 %213, 80
  %216 = sub nsw i32 80, %215
  %217 = icmp slt i32 %214, %216
  br i1 %217, label %218, label %227

218:                                              ; preds = %212
  %219 = getelementptr inbounds i32, ptr %5, i32 %214
  %220 = load i32, ptr %219, align 4, !tbaa !6
  %221 = add nuw nsw i32 %214, 1
  %222 = getelementptr inbounds i32, ptr %5, i32 %221
  %223 = load i32, ptr %222, align 4, !tbaa !6
  %224 = icmp sgt i32 %220, %223
  br i1 %224, label %225, label %227

225:                                              ; preds = %218
  store i32 %223, ptr %219, align 4, !tbaa !6
  %226 = and i32 %220, 255
  store i32 %226, ptr %222, align 4, !tbaa !6
  br label %227

227:                                              ; preds = %225, %218, %212
  %228 = add nuw nsw i32 %213, 1
  %229 = icmp eq i32 %228, 3240
  br i1 %229, label %230, label %212, !llvm.loop !10

230:                                              ; preds = %227
  %231 = load i32, ptr %175, align 4, !tbaa !6
  %232 = and i32 %231, 255
  %233 = mul i32 %208, %2
  %234 = lshr i32 %233, 1
  %235 = add nuw i32 %234, %209
  %236 = mul i32 %8, %206
  %237 = add i32 %235, %236
  %238 = getelementptr inbounds i32, ptr %10, i32 %237
  store i32 %232, ptr %238, align 4, !tbaa !6
  %239 = add nuw nsw i32 %199, 1
  %240 = icmp eq i32 %239, %25
  br i1 %240, label %193, label %198, !llvm.loop !19

241:                                              ; preds = %198, %241
  %242 = phi i32 [ 0, %198 ], [ %257, %241 ]
  %243 = trunc i32 %242 to i8
  %244 = udiv i8 %243, 9
  %245 = zext i8 %244 to i32
  %246 = urem i8 %243, 9
  %247 = zext i8 %246 to i32
  %248 = add i32 %211, %245
  %249 = mul i32 %248, %11
  %250 = add nuw i32 %209, %247
  %251 = add i32 %250, %249
  %252 = getelementptr inbounds i32, ptr %15, i32 %251
  %253 = load i32, ptr %252, align 4, !tbaa !6
  %254 = mul nuw nsw i32 %245, 9
  %255 = add nuw nsw i32 %254, %247
  %256 = getelementptr inbounds [81 x i32], ptr %5, i32 0, i32 %255
  store i32 %253, ptr %256, align 4, !tbaa !6
  %257 = add nuw nsw i32 %242, 1
  %258 = icmp eq i32 %257, 81
  br i1 %258, label %212, label %241, !llvm.loop !20

259:                                              ; preds = %260, %193
  tail call void @free(ptr noundef %10) #8
  tail call void @free(ptr noundef %15) #8
  call void @llvm.lifetime.end.p0(i64 324, ptr nonnull %5) #8
  ret void

260:                                              ; preds = %194, %260
  %261 = phi i32 [ 0, %194 ], [ %296, %260 ]
  %262 = phi i32 [ 0, %194 ], [ %268, %260 ]
  %263 = urem i32 %261, %6
  %264 = icmp eq i32 %263, 0
  %265 = icmp ne i32 %261, 0
  %266 = and i1 %265, %264
  %267 = zext i1 %266 to i32
  %268 = add i32 %262, %267
  %269 = mul i32 %268, %2
  %270 = lshr i32 %269, 1
  %271 = add nuw i32 %270, %263
  %272 = getelementptr inbounds i32, ptr %10, i32 %271
  %273 = load i32, ptr %272, align 4, !tbaa !6
  %274 = shl i32 %268, 1
  %275 = mul i32 %274, %2
  %276 = shl nuw i32 %263, 1
  %277 = add i32 %275, %276
  %278 = getelementptr inbounds i32, ptr %1, i32 %277
  store i32 %273, ptr %278, align 4, !tbaa !6
  %279 = add i32 %271, %8
  %280 = getelementptr inbounds i32, ptr %10, i32 %279
  %281 = load i32, ptr %280, align 4, !tbaa !6
  %282 = or i32 %277, 1
  %283 = getelementptr inbounds i32, ptr %1, i32 %282
  store i32 %281, ptr %283, align 4, !tbaa !6
  %284 = add i32 %271, %195
  %285 = getelementptr inbounds i32, ptr %10, i32 %284
  %286 = load i32, ptr %285, align 4, !tbaa !6
  %287 = or i32 %274, 1
  %288 = mul i32 %287, %2
  %289 = add i32 %288, %276
  %290 = getelementptr inbounds i32, ptr %1, i32 %289
  store i32 %286, ptr %290, align 4, !tbaa !6
  %291 = add i32 %271, %196
  %292 = getelementptr inbounds i32, ptr %10, i32 %291
  %293 = load i32, ptr %292, align 4, !tbaa !6
  %294 = add i32 %289, 1
  %295 = getelementptr inbounds i32, ptr %1, i32 %294
  store i32 %293, ptr %295, align 4, !tbaa !6
  %296 = add nuw nsw i32 %261, 1
  %297 = icmp eq i32 %296, %197
  br i1 %297, label %259, label %260, !llvm.loop !21
}

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i32 noundef) local_unnamed_addr #3

; Function Attrs: nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i32(ptr nocapture writeonly, i8, i32, i1 immarg) #4

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr nocapture noundef) local_unnamed_addr #5

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umax.i32(i32, i32) #6

attributes #0 = { mustprogress nofree norecurse nosync nounwind memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #4 = { nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #5 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #6 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #7 = { nounwind allocsize(0) }
attributes #8 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"NumRegisterParameters", i32 0}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 8, !"PIC Level", i32 2}
!3 = !{i32 7, !"PIE Level", i32 2}
!4 = !{i32 7, !"uwtable", i32 2}
!5 = !{!"Ubuntu clang version 16.0.6 (++20231112100421+7cbf1a259152-1~exp1~20231112100514.107)"}
!6 = !{!7, !7, i64 0}
!7 = !{!"int", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C++ TBAA"}
!10 = distinct !{!10, !11, !12}
!11 = !{!"llvm.loop.mustprogress"}
!12 = !{!"llvm.loop.unroll.disable"}
!13 = distinct !{!13, !11, !12}
!14 = distinct !{!14, !11, !12}
!15 = distinct !{!15, !11, !12}
!16 = distinct !{!16, !11, !12}
!17 = distinct !{!17, !11, !12}
!18 = distinct !{!18, !11, !12}
!19 = distinct !{!19, !11, !12}
!20 = distinct !{!20, !11, !12}
!21 = distinct !{!21, !11, !12}
