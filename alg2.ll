; ModuleID = './test/dfg/src/alg2.bc'
source_filename = "self_tests/src_huawei/alg2.cpp"
target datalayout = "e-m:e-p:32:32-p270:32:32-p271:32:32-p272:64:64-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%struct.alg2_register = type { [15 x i32] }

; Function Attrs: mustprogress nounwind uwtable
define dso_local void @_Z9alg2_funcPtS_jjj(ptr nocapture noundef readonly %0, ptr nocapture noundef writeonly %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #0 {
  %6 = alloca [15 x i32], align 4
  %7 = alloca %struct.alg2_register, align 4
  %8 = alloca [9 x [9 x i32]], align 4
  %9 = lshr i32 %2, 1
  %10 = lshr i32 %3, 1
  %11 = mul i32 %10, %9
  %12 = shl i32 %11, 2
  %13 = shl i32 %11, 4
  %14 = tail call noalias ptr @malloc(i32 noundef %13) #6
  %15 = add nuw i32 %9, 8
  %16 = add nuw i32 %10, 8
  %17 = mul i32 %16, %15
  %18 = shl i32 %17, 4
  %19 = tail call noalias ptr @malloc(i32 noundef %18) #6
  %20 = mul i32 %3, %2
  %21 = lshr i32 %20, 2
  %22 = icmp ult i32 %20, 4
  br i1 %22, label %27, label %23

23:                                               ; preds = %5
  %24 = shl i32 %11, 1
  %25 = mul i32 %11, 3
  %26 = tail call i32 @llvm.umax.i32(i32 %21, i32 1)
  br label %31

27:                                               ; preds = %31, %5
  %28 = icmp eq i32 %12, 0
  br i1 %28, label %73, label %29

29:                                               ; preds = %27
  %30 = add nsw i32 %9, -1
  br label %77

31:                                               ; preds = %23, %31
  %32 = phi i32 [ 0, %23 ], [ %39, %31 ]
  %33 = phi i32 [ 0, %23 ], [ %71, %31 ]
  %34 = urem i32 %33, %9
  %35 = icmp eq i32 %34, 0
  %36 = icmp ne i32 %33, 0
  %37 = and i1 %36, %35
  %38 = zext i1 %37 to i32
  %39 = add i32 %32, %38
  %40 = shl i32 %39, 1
  %41 = mul i32 %40, %2
  %42 = shl nuw i32 %34, 1
  %43 = add i32 %41, %42
  %44 = getelementptr inbounds i16, ptr %0, i32 %43
  %45 = load i16, ptr %44, align 2, !tbaa !6
  %46 = zext i16 %45 to i32
  %47 = mul i32 %39, %2
  %48 = lshr i32 %47, 1
  %49 = add nuw i32 %48, %34
  %50 = getelementptr inbounds i32, ptr %14, i32 %49
  store i32 %46, ptr %50, align 4, !tbaa !10
  %51 = or i32 %43, 1
  %52 = getelementptr inbounds i16, ptr %0, i32 %51
  %53 = load i16, ptr %52, align 2, !tbaa !6
  %54 = zext i16 %53 to i32
  %55 = add i32 %49, %11
  %56 = getelementptr inbounds i32, ptr %14, i32 %55
  store i32 %54, ptr %56, align 4, !tbaa !10
  %57 = or i32 %40, 1
  %58 = mul i32 %57, %2
  %59 = add i32 %58, %42
  %60 = getelementptr inbounds i16, ptr %0, i32 %59
  %61 = load i16, ptr %60, align 2, !tbaa !6
  %62 = zext i16 %61 to i32
  %63 = add i32 %49, %24
  %64 = getelementptr inbounds i32, ptr %14, i32 %63
  store i32 %62, ptr %64, align 4, !tbaa !10
  %65 = add i32 %59, 1
  %66 = getelementptr inbounds i16, ptr %0, i32 %65
  %67 = load i16, ptr %66, align 2, !tbaa !6
  %68 = zext i16 %67 to i32
  %69 = add i32 %49, %25
  %70 = getelementptr inbounds i32, ptr %14, i32 %69
  store i32 %68, ptr %70, align 4, !tbaa !10
  %71 = add nuw nsw i32 %33, 1
  %72 = icmp eq i32 %71, %26
  br i1 %72, label %27, label %31, !llvm.loop !12

73:                                               ; preds = %99, %27
  %74 = phi i32 [ 0, %27 ], [ %120, %99 ]
  %75 = shl i32 %10, 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %158, label %127

77:                                               ; preds = %29, %99
  %78 = phi i32 [ 0, %29 ], [ %121, %99 ]
  %79 = phi i32 [ 0, %29 ], [ %119, %99 ]
  %80 = phi i32 [ 0, %29 ], [ %120, %99 ]
  %81 = phi i32 [ 0, %29 ], [ %102, %99 ]
  %82 = icmp eq i32 %79, 0
  br i1 %82, label %83, label %86

83:                                               ; preds = %77
  %84 = sub i32 %79, %80
  %85 = urem i32 %84, %9
  br label %99

86:                                               ; preds = %77
  %87 = urem i32 %79, %11
  %88 = icmp eq i32 %87, 0
  %89 = zext i1 %88 to i32
  %90 = add i32 %81, %89
  %91 = select i1 %88, i32 %79, i32 %80
  %92 = sub i32 %79, %91
  %93 = urem i32 %92, %9
  %94 = icmp eq i32 %93, 0
  %95 = icmp ugt i32 %79, %91
  %96 = select i1 %94, i1 %95, i1 false
  %97 = zext i1 %96 to i32
  %98 = add i32 %78, %97
  br label %99

99:                                               ; preds = %83, %86
  %100 = phi i32 [ %85, %83 ], [ %93, %86 ]
  %101 = phi i32 [ %80, %83 ], [ %91, %86 ]
  %102 = phi i32 [ %81, %83 ], [ %90, %86 ]
  %103 = phi i32 [ %78, %83 ], [ %98, %86 ]
  %104 = mul i32 %103, %2
  %105 = lshr i32 %104, 1
  %106 = mul i32 %11, %102
  %107 = add i32 %106, %100
  %108 = add i32 %107, %105
  %109 = getelementptr inbounds i32, ptr %14, i32 %108
  %110 = load i32, ptr %109, align 4, !tbaa !10
  %111 = add i32 %103, 4
  %112 = mul i32 %102, %16
  %113 = add i32 %111, %112
  %114 = mul i32 %113, %15
  %115 = add nuw i32 %100, 4
  %116 = add i32 %115, %114
  %117 = getelementptr inbounds i32, ptr %19, i32 %116
  store i32 %110, ptr %117, align 4, !tbaa !10
  %118 = icmp eq i32 %100, %30
  %119 = add nuw i32 %79, 1
  %120 = select i1 %118, i32 %119, i32 %101
  %121 = select i1 %118, i32 0, i32 %103
  %122 = icmp eq i32 %119, %12
  br i1 %122, label %73, label %77, !llvm.loop !15

123:                                              ; preds = %138
  br i1 %76, label %158, label %124

124:                                              ; preds = %123
  %125 = add nsw i32 %9, -1
  %126 = add nuw i32 %9, 4
  br label %164

127:                                              ; preds = %73, %138
  %128 = phi i32 [ %156, %138 ], [ 0, %73 ]
  %129 = phi i32 [ %140, %138 ], [ %74, %73 ]
  %130 = phi i32 [ %139, %138 ], [ 0, %73 ]
  %131 = icmp eq i32 %128, 0
  br i1 %131, label %138, label %132

132:                                              ; preds = %127
  %133 = urem i32 %128, %10
  %134 = icmp eq i32 %133, 0
  %135 = zext i1 %134 to i32
  %136 = add i32 %130, %135
  %137 = select i1 %134, i32 %128, i32 %129
  br label %138

138:                                              ; preds = %132, %127
  %139 = phi i32 [ %130, %127 ], [ %136, %132 ]
  %140 = phi i32 [ %129, %127 ], [ %137, %132 ]
  %141 = sub i32 %128, %140
  %142 = lshr i32 %141, 2
  %143 = and i32 %128, 3
  %144 = mul i32 %142, %2
  %145 = lshr i32 %144, 1
  %146 = mul i32 %11, %139
  %147 = add i32 %145, %146
  %148 = getelementptr inbounds i32, ptr %14, i32 %147
  %149 = load i32, ptr %148, align 4, !tbaa !10
  %150 = mul i32 %139, %16
  %151 = add i32 %150, 4
  %152 = add i32 %151, %142
  %153 = mul i32 %152, %15
  %154 = add i32 %153, %143
  %155 = getelementptr inbounds i32, ptr %19, i32 %154
  store i32 %149, ptr %155, align 4, !tbaa !10
  %156 = add nuw i32 %128, 1
  %157 = icmp eq i32 %156, %75
  br i1 %157, label %123, label %127, !llvm.loop !16

158:                                              ; preds = %175, %73, %123
  %159 = phi i32 [ %140, %123 ], [ %74, %73 ], [ %177, %175 ]
  %160 = shl i32 %15, 4
  %161 = icmp eq i32 %160, 0
  br i1 %161, label %231, label %162

162:                                              ; preds = %158
  %163 = shl i32 %15, 2
  br label %203

164:                                              ; preds = %124, %175
  %165 = phi i32 [ 0, %124 ], [ %195, %175 ]
  %166 = phi i32 [ %140, %124 ], [ %177, %175 ]
  %167 = phi i32 [ 0, %124 ], [ %176, %175 ]
  %168 = icmp eq i32 %165, 0
  br i1 %168, label %175, label %169

169:                                              ; preds = %164
  %170 = urem i32 %165, %10
  %171 = icmp eq i32 %170, 0
  %172 = zext i1 %171 to i32
  %173 = add i32 %167, %172
  %174 = select i1 %171, i32 %165, i32 %166
  br label %175

175:                                              ; preds = %169, %164
  %176 = phi i32 [ %167, %164 ], [ %173, %169 ]
  %177 = phi i32 [ %166, %164 ], [ %174, %169 ]
  %178 = sub i32 %165, %177
  %179 = lshr i32 %178, 2
  %180 = and i32 %165, 3
  %181 = mul i32 %179, %2
  %182 = lshr i32 %181, 1
  %183 = mul i32 %11, %176
  %184 = add i32 %125, %183
  %185 = add i32 %184, %182
  %186 = getelementptr inbounds i32, ptr %14, i32 %185
  %187 = load i32, ptr %186, align 4, !tbaa !10
  %188 = mul i32 %176, %16
  %189 = add i32 %188, 4
  %190 = add i32 %189, %179
  %191 = mul i32 %190, %15
  %192 = add i32 %126, %180
  %193 = add i32 %192, %191
  %194 = getelementptr inbounds i32, ptr %19, i32 %193
  store i32 %187, ptr %194, align 4, !tbaa !10
  %195 = add nuw i32 %165, 1
  %196 = icmp eq i32 %195, %75
  br i1 %196, label %158, label %164, !llvm.loop !17

197:                                              ; preds = %214
  br i1 %161, label %231, label %198

198:                                              ; preds = %197
  %199 = shl i32 %15, 2
  %200 = add nuw i32 %10, 4
  %201 = add nuw i32 %10, 3
  %202 = mul i32 %201, %15
  br label %450

203:                                              ; preds = %162, %214
  %204 = phi i32 [ 0, %162 ], [ %229, %214 ]
  %205 = phi i32 [ %159, %162 ], [ %216, %214 ]
  %206 = phi i32 [ 0, %162 ], [ %215, %214 ]
  %207 = icmp eq i32 %204, 0
  br i1 %207, label %214, label %208

208:                                              ; preds = %203
  %209 = urem i32 %204, %163
  %210 = icmp eq i32 %209, 0
  %211 = zext i1 %210 to i32
  %212 = add i32 %206, %211
  %213 = select i1 %210, i32 %204, i32 %205
  br label %214

214:                                              ; preds = %208, %203
  %215 = phi i32 [ %206, %203 ], [ %212, %208 ]
  %216 = phi i32 [ %205, %203 ], [ %213, %208 ]
  %217 = sub i32 %204, %216
  %218 = urem i32 %204, %15
  %219 = mul i32 %17, %215
  %220 = add i32 %219, %218
  %221 = add i32 %220, %163
  %222 = getelementptr inbounds i32, ptr %19, i32 %221
  %223 = load i32, ptr %222, align 4, !tbaa !10
  %224 = freeze i32 %217
  %225 = urem i32 %224, %15
  %226 = add i32 %220, %224
  %227 = sub i32 %226, %225
  %228 = getelementptr inbounds i32, ptr %19, i32 %227
  store i32 %223, ptr %228, align 4, !tbaa !10
  %229 = add nuw i32 %204, 1
  %230 = icmp eq i32 %229, %160
  br i1 %230, label %197, label %203, !llvm.loop !18

231:                                              ; preds = %461, %158, %197
  %232 = phi i32 [ 0, %197 ], [ 0, %158 ], [ %466, %461 ]
  call void @llvm.lifetime.start.p0(i64 60, ptr nonnull %7) #7
  call void @llvm.lifetime.start.p0(i64 60, ptr nonnull %6) #7
  %233 = shl i32 %4, 1
  %234 = mul i32 %233, %4
  store i32 1, ptr %6, align 4, !tbaa !10
  %235 = getelementptr inbounds i32, ptr %6, i32 1
  %236 = udiv i32 -1, %234
  %237 = uitofp i32 %236 to double
  %238 = tail call double @exp(double noundef %237) #7
  %239 = fptoui double %238 to i32
  store i32 %239, ptr %235, align 4, !tbaa !10
  %240 = getelementptr inbounds i32, ptr %6, i32 2
  %241 = udiv i32 -2, %234
  %242 = uitofp i32 %241 to double
  %243 = tail call double @exp(double noundef %242) #7
  %244 = fptoui double %243 to i32
  store i32 %244, ptr %240, align 4, !tbaa !10
  %245 = getelementptr inbounds i32, ptr %6, i32 3
  %246 = udiv i32 -4, %234
  %247 = uitofp i32 %246 to double
  %248 = tail call double @exp(double noundef %247) #7
  %249 = fptoui double %248 to i32
  store i32 %249, ptr %245, align 4, !tbaa !10
  %250 = getelementptr inbounds i32, ptr %6, i32 4
  %251 = udiv i32 -5, %234
  %252 = uitofp i32 %251 to double
  %253 = tail call double @exp(double noundef %252) #7
  %254 = fptoui double %253 to i32
  store i32 %254, ptr %250, align 4, !tbaa !10
  %255 = getelementptr inbounds i32, ptr %6, i32 5
  %256 = udiv i32 -8, %234
  %257 = uitofp i32 %256 to double
  %258 = tail call double @exp(double noundef %257) #7
  %259 = fptoui double %258 to i32
  store i32 %259, ptr %255, align 4, !tbaa !10
  %260 = getelementptr inbounds i32, ptr %6, i32 6
  %261 = udiv i32 -9, %234
  %262 = uitofp i32 %261 to double
  %263 = tail call double @exp(double noundef %262) #7
  %264 = fptoui double %263 to i32
  store i32 %264, ptr %260, align 4, !tbaa !10
  %265 = getelementptr inbounds i32, ptr %6, i32 7
  %266 = udiv i32 -10, %234
  %267 = uitofp i32 %266 to double
  %268 = tail call double @exp(double noundef %267) #7
  %269 = fptoui double %268 to i32
  store i32 %269, ptr %265, align 4, !tbaa !10
  %270 = getelementptr inbounds i32, ptr %6, i32 8
  %271 = udiv i32 -13, %234
  %272 = uitofp i32 %271 to double
  %273 = tail call double @exp(double noundef %272) #7
  %274 = fptoui double %273 to i32
  store i32 %274, ptr %270, align 4, !tbaa !10
  %275 = getelementptr inbounds i32, ptr %6, i32 9
  %276 = udiv i32 -18, %234
  %277 = uitofp i32 %276 to double
  %278 = tail call double @exp(double noundef %277) #7
  %279 = fptoui double %278 to i32
  store i32 %279, ptr %275, align 4, !tbaa !10
  %280 = getelementptr inbounds i32, ptr %6, i32 10
  %281 = udiv i32 -16, %234
  %282 = uitofp i32 %281 to double
  %283 = tail call double @exp(double noundef %282) #7
  %284 = fptoui double %283 to i32
  store i32 %284, ptr %280, align 4, !tbaa !10
  %285 = getelementptr inbounds i32, ptr %6, i32 11
  %286 = udiv i32 -17, %234
  %287 = uitofp i32 %286 to double
  %288 = tail call double @exp(double noundef %287) #7
  %289 = fptoui double %288 to i32
  store i32 %289, ptr %285, align 4, !tbaa !10
  %290 = getelementptr inbounds i32, ptr %6, i32 12
  %291 = udiv i32 -20, %234
  %292 = uitofp i32 %291 to double
  %293 = tail call double @exp(double noundef %292) #7
  %294 = fptoui double %293 to i32
  store i32 %294, ptr %290, align 4, !tbaa !10
  %295 = getelementptr inbounds i32, ptr %6, i32 13
  %296 = udiv i32 -25, %234
  %297 = uitofp i32 %296 to double
  %298 = tail call double @exp(double noundef %297) #7
  %299 = fptoui double %298 to i32
  store i32 %299, ptr %295, align 4, !tbaa !10
  %300 = getelementptr inbounds i32, ptr %6, i32 14
  %301 = udiv i32 -32, %234
  %302 = uitofp i32 %301 to double
  %303 = tail call double @exp(double noundef %302) #7
  %304 = fptoui double %303 to i32
  store i32 %304, ptr %300, align 4, !tbaa !10
  %305 = shl i32 %239, 2
  %306 = add i32 %249, %244
  %307 = add i32 %306, %259
  %308 = add i32 %307, %264
  %309 = add i32 %308, %279
  %310 = add i32 %309, %284
  %311 = add i32 %310, %304
  %312 = shl i32 %311, 2
  %313 = add i32 %269, %254
  %314 = add i32 %313, %274
  %315 = add i32 %314, %289
  %316 = add i32 %315, %294
  %317 = add i32 %316, %299
  %318 = shl i32 %317, 3
  %319 = or i32 %305, 1
  %320 = add i32 %319, %318
  %321 = add i32 %320, %312
  br label %322

322:                                              ; preds = %322, %231
  %323 = phi i32 [ 0, %231 ], [ %327, %322 ]
  %324 = getelementptr inbounds [15 x i32], ptr %6, i32 0, i32 %323
  %325 = load i32, ptr %324, align 4, !tbaa !10
  %326 = udiv i32 %325, %321
  store i32 %326, ptr %324, align 4, !tbaa !10
  %327 = add nuw nsw i32 %323, 1
  %328 = icmp eq i32 %327, 15
  br i1 %328, label %329, label %322, !llvm.loop !19

329:                                              ; preds = %322, %329
  %330 = phi i32 [ %335, %329 ], [ 0, %322 ]
  %331 = getelementptr inbounds [15 x i32], ptr %6, i32 0, i32 %330
  %332 = load i32, ptr %331, align 4, !tbaa !10
  %333 = shl i32 %332, 10
  %334 = getelementptr inbounds [15 x i32], ptr %7, i32 0, i32 %330
  store i32 %333, ptr %334, align 4, !tbaa !10
  %335 = add nuw nsw i32 %330, 1
  %336 = icmp eq i32 %335, 15
  br i1 %336, label %337, label %329, !llvm.loop !20

337:                                              ; preds = %329
  call void @llvm.lifetime.end.p0(i64 60, ptr nonnull %6) #7
  %338 = load i32, ptr %7, align 4, !tbaa !10
  %339 = getelementptr inbounds i8, ptr %7, i32 4
  %340 = load i32, ptr %339, align 4, !tbaa !10
  %341 = getelementptr inbounds i8, ptr %7, i32 8
  %342 = load i32, ptr %341, align 4, !tbaa !10
  %343 = getelementptr inbounds i8, ptr %7, i32 12
  %344 = load i32, ptr %343, align 4, !tbaa !10
  %345 = getelementptr inbounds i8, ptr %7, i32 16
  %346 = load i32, ptr %345, align 4, !tbaa !10
  %347 = getelementptr inbounds i8, ptr %7, i32 20
  %348 = load i32, ptr %347, align 4, !tbaa !10
  %349 = getelementptr inbounds i8, ptr %7, i32 24
  %350 = load i32, ptr %349, align 4, !tbaa !10
  %351 = getelementptr inbounds i8, ptr %7, i32 28
  %352 = load i32, ptr %351, align 4, !tbaa !10
  %353 = getelementptr inbounds i8, ptr %7, i32 32
  %354 = load i32, ptr %353, align 4, !tbaa !10
  %355 = getelementptr inbounds i8, ptr %7, i32 36
  %356 = load i32, ptr %355, align 4, !tbaa !10
  %357 = getelementptr inbounds i8, ptr %7, i32 40
  %358 = load i32, ptr %357, align 4, !tbaa !10
  %359 = getelementptr inbounds i8, ptr %7, i32 44
  %360 = load i32, ptr %359, align 4, !tbaa !10
  %361 = getelementptr inbounds i8, ptr %7, i32 48
  %362 = load i32, ptr %361, align 4, !tbaa !10
  %363 = getelementptr inbounds i8, ptr %7, i32 52
  %364 = load i32, ptr %363, align 4, !tbaa !10
  %365 = getelementptr inbounds i8, ptr %7, i32 56
  %366 = load i32, ptr %365, align 4, !tbaa !10
  call void @llvm.lifetime.start.p0(i64 324, ptr nonnull %8) #7
  store i32 %366, ptr %8, align 4, !tbaa !10
  %367 = getelementptr inbounds i32, ptr %8, i32 1
  store i32 %364, ptr %367, align 4, !tbaa !10
  %368 = getelementptr inbounds i32, ptr %8, i32 2
  store i32 %362, ptr %368, align 4, !tbaa !10
  %369 = getelementptr inbounds i32, ptr %8, i32 3
  store i32 %360, ptr %369, align 4, !tbaa !10
  %370 = getelementptr inbounds i32, ptr %8, i32 4
  store i32 %358, ptr %370, align 4, !tbaa !10
  %371 = getelementptr inbounds i32, ptr %8, i32 5
  store i32 %360, ptr %371, align 4, !tbaa !10
  %372 = getelementptr inbounds i32, ptr %8, i32 6
  store i32 %362, ptr %372, align 4, !tbaa !10
  %373 = getelementptr inbounds i32, ptr %8, i32 7
  store i32 %364, ptr %373, align 4, !tbaa !10
  %374 = getelementptr inbounds i32, ptr %8, i32 8
  store i32 %366, ptr %374, align 4, !tbaa !10
  %375 = getelementptr inbounds [9 x i32], ptr %8, i32 1
  store i32 %364, ptr %375, align 4, !tbaa !10
  %376 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 1
  store i32 %356, ptr %376, align 4, !tbaa !10
  %377 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 2
  store i32 %354, ptr %377, align 4, !tbaa !10
  %378 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 3
  store i32 %352, ptr %378, align 4, !tbaa !10
  %379 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 4
  store i32 %350, ptr %379, align 4, !tbaa !10
  %380 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 5
  store i32 %352, ptr %380, align 4, !tbaa !10
  %381 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 6
  store i32 %354, ptr %381, align 4, !tbaa !10
  %382 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 7
  store i32 %356, ptr %382, align 4, !tbaa !10
  %383 = getelementptr inbounds [9 x i32], ptr %8, i32 1, i32 8
  store i32 %364, ptr %383, align 4, !tbaa !10
  %384 = getelementptr inbounds [9 x i32], ptr %8, i32 2
  store i32 %362, ptr %384, align 4, !tbaa !10
  %385 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 1
  store i32 %354, ptr %385, align 4, !tbaa !10
  %386 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 2
  store i32 %348, ptr %386, align 4, !tbaa !10
  %387 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 3
  store i32 %346, ptr %387, align 4, !tbaa !10
  %388 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 4
  store i32 %344, ptr %388, align 4, !tbaa !10
  %389 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 5
  store i32 %346, ptr %389, align 4, !tbaa !10
  %390 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 6
  store i32 %348, ptr %390, align 4, !tbaa !10
  %391 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 7
  store i32 %354, ptr %391, align 4, !tbaa !10
  %392 = getelementptr inbounds [9 x i32], ptr %8, i32 2, i32 8
  store i32 %362, ptr %392, align 4, !tbaa !10
  %393 = getelementptr inbounds [9 x i32], ptr %8, i32 3
  store i32 %360, ptr %393, align 4, !tbaa !10
  %394 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 1
  store i32 %352, ptr %394, align 4, !tbaa !10
  %395 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 2
  store i32 %346, ptr %395, align 4, !tbaa !10
  %396 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 3
  store i32 %342, ptr %396, align 4, !tbaa !10
  %397 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 4
  store i32 %340, ptr %397, align 4, !tbaa !10
  %398 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 5
  store i32 %342, ptr %398, align 4, !tbaa !10
  %399 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 6
  store i32 %346, ptr %399, align 4, !tbaa !10
  %400 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 7
  store i32 %352, ptr %400, align 4, !tbaa !10
  %401 = getelementptr inbounds [9 x i32], ptr %8, i32 3, i32 8
  store i32 %360, ptr %401, align 4, !tbaa !10
  %402 = getelementptr inbounds [9 x i32], ptr %8, i32 4
  store i32 %358, ptr %402, align 4, !tbaa !10
  %403 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 1
  store i32 %350, ptr %403, align 4, !tbaa !10
  %404 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 2
  store i32 %344, ptr %404, align 4, !tbaa !10
  %405 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 3
  store i32 %340, ptr %405, align 4, !tbaa !10
  %406 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 4
  store i32 %338, ptr %406, align 4, !tbaa !10
  %407 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 5
  store i32 %340, ptr %407, align 4, !tbaa !10
  %408 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 6
  store i32 %344, ptr %408, align 4, !tbaa !10
  %409 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 7
  store i32 %350, ptr %409, align 4, !tbaa !10
  %410 = getelementptr inbounds [9 x i32], ptr %8, i32 4, i32 8
  store i32 %358, ptr %410, align 4, !tbaa !10
  %411 = getelementptr inbounds [9 x i32], ptr %8, i32 5
  store i32 %360, ptr %411, align 4, !tbaa !10
  %412 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 1
  store i32 %352, ptr %412, align 4, !tbaa !10
  %413 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 2
  store i32 %346, ptr %413, align 4, !tbaa !10
  %414 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 3
  store i32 %342, ptr %414, align 4, !tbaa !10
  %415 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 4
  store i32 %340, ptr %415, align 4, !tbaa !10
  %416 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 5
  store i32 %342, ptr %416, align 4, !tbaa !10
  %417 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 6
  store i32 %346, ptr %417, align 4, !tbaa !10
  %418 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 7
  store i32 %352, ptr %418, align 4, !tbaa !10
  %419 = getelementptr inbounds [9 x i32], ptr %8, i32 5, i32 8
  store i32 %360, ptr %419, align 4, !tbaa !10
  %420 = getelementptr inbounds [9 x i32], ptr %8, i32 6
  store i32 %362, ptr %420, align 4, !tbaa !10
  %421 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 1
  store i32 %354, ptr %421, align 4, !tbaa !10
  %422 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 2
  store i32 %348, ptr %422, align 4, !tbaa !10
  %423 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 3
  store i32 %346, ptr %423, align 4, !tbaa !10
  %424 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 4
  store i32 %344, ptr %424, align 4, !tbaa !10
  %425 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 5
  store i32 %346, ptr %425, align 4, !tbaa !10
  %426 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 6
  store i32 %348, ptr %426, align 4, !tbaa !10
  %427 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 7
  store i32 %354, ptr %427, align 4, !tbaa !10
  %428 = getelementptr inbounds [9 x i32], ptr %8, i32 6, i32 8
  store i32 %362, ptr %428, align 4, !tbaa !10
  %429 = getelementptr inbounds [9 x i32], ptr %8, i32 7
  store i32 %364, ptr %429, align 4, !tbaa !10
  %430 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 1
  store i32 %356, ptr %430, align 4, !tbaa !10
  %431 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 2
  store i32 %354, ptr %431, align 4, !tbaa !10
  %432 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 3
  store i32 %352, ptr %432, align 4, !tbaa !10
  %433 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 4
  store i32 %350, ptr %433, align 4, !tbaa !10
  %434 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 5
  store i32 %352, ptr %434, align 4, !tbaa !10
  %435 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 6
  store i32 %354, ptr %435, align 4, !tbaa !10
  %436 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 7
  store i32 %356, ptr %436, align 4, !tbaa !10
  %437 = getelementptr inbounds [9 x i32], ptr %8, i32 7, i32 8
  store i32 %364, ptr %437, align 4, !tbaa !10
  %438 = getelementptr inbounds [9 x i32], ptr %8, i32 8
  store i32 %366, ptr %438, align 4, !tbaa !10
  %439 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 1
  store i32 %364, ptr %439, align 4, !tbaa !10
  %440 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 2
  store i32 %362, ptr %440, align 4, !tbaa !10
  %441 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 3
  store i32 %360, ptr %441, align 4, !tbaa !10
  %442 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 4
  store i32 %358, ptr %442, align 4, !tbaa !10
  %443 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 5
  store i32 %360, ptr %443, align 4, !tbaa !10
  %444 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 6
  store i32 %362, ptr %444, align 4, !tbaa !10
  %445 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 7
  store i32 %364, ptr %445, align 4, !tbaa !10
  %446 = getelementptr inbounds [9 x i32], ptr %8, i32 8, i32 8
  store i32 %366, ptr %446, align 4, !tbaa !10
  %447 = mul i32 %11, 81
  %448 = mul i32 %11, 324
  %449 = icmp eq i32 %448, 0
  br i1 %449, label %480, label %478

450:                                              ; preds = %198, %461
  %451 = phi i32 [ 0, %198 ], [ %476, %461 ]
  %452 = phi i32 [ %216, %198 ], [ %463, %461 ]
  %453 = phi i32 [ 0, %198 ], [ %462, %461 ]
  %454 = icmp eq i32 %451, 0
  br i1 %454, label %461, label %455

455:                                              ; preds = %450
  %456 = urem i32 %451, %199
  %457 = icmp eq i32 %456, 0
  %458 = zext i1 %457 to i32
  %459 = add i32 %453, %458
  %460 = select i1 %457, i32 %451, i32 %452
  br label %461

461:                                              ; preds = %455, %450
  %462 = phi i32 [ %453, %450 ], [ %459, %455 ]
  %463 = phi i32 [ %452, %450 ], [ %460, %455 ]
  %464 = sub i32 %451, %463
  %465 = udiv i32 %464, %15
  %466 = add i32 %200, %465
  %467 = urem i32 %451, %15
  %468 = mul i32 %17, %462
  %469 = add i32 %467, %468
  %470 = add i32 %469, %202
  %471 = getelementptr inbounds i32, ptr %19, i32 %470
  %472 = load i32, ptr %471, align 4, !tbaa !10
  %473 = mul i32 %466, %15
  %474 = add i32 %469, %473
  %475 = getelementptr inbounds i32, ptr %19, i32 %474
  store i32 %472, ptr %475, align 4, !tbaa !10
  %476 = add nuw i32 %451, 1
  %477 = icmp eq i32 %476, %160
  br i1 %477, label %231, label %450, !llvm.loop !21

478:                                              ; preds = %337
  %479 = mul i32 %9, 81
  br label %485

480:                                              ; preds = %550, %337
  br i1 %22, label %557, label %481

481:                                              ; preds = %480
  %482 = shl i32 %11, 1
  %483 = mul i32 %11, 3
  %484 = tail call i32 @llvm.umax.i32(i32 %21, i32 1)
  br label %558

485:                                              ; preds = %478, %550
  %486 = phi i32 [ 0, %478 ], [ %553, %550 ]
  %487 = phi i32 [ 0, %478 ], [ %501, %550 ]
  %488 = phi i32 [ %232, %478 ], [ %555, %550 ]
  %489 = phi i32 [ 0, %478 ], [ %539, %550 ]
  %490 = phi i32 [ 0, %478 ], [ %554, %550 ]
  %491 = phi i32 [ 0, %478 ], [ %500, %550 ]
  %492 = icmp eq i32 %486, 0
  br i1 %492, label %499, label %493

493:                                              ; preds = %485
  %494 = urem i32 %486, %447
  %495 = icmp eq i32 %494, 0
  %496 = zext i1 %495 to i32
  %497 = add i32 %491, %496
  %498 = select i1 %495, i32 %486, i32 %487
  br label %499

499:                                              ; preds = %493, %485
  %500 = phi i32 [ %491, %485 ], [ %497, %493 ]
  %501 = phi i32 [ %487, %485 ], [ %498, %493 ]
  %502 = icmp eq i32 %486, %501
  br i1 %502, label %508, label %503

503:                                              ; preds = %499
  %504 = sub i32 %486, %501
  %505 = urem i32 %504, %479
  %506 = icmp eq i32 %505, 0
  %507 = select i1 %506, i32 %486, i32 %490
  br label %508

508:                                              ; preds = %503, %499
  %509 = phi i32 [ %490, %499 ], [ %507, %503 ]
  %510 = icmp eq i32 %486, %509
  br i1 %510, label %517, label %511

511:                                              ; preds = %508
  %512 = sub i32 %486, %509
  %513 = urem i32 %512, 81
  %514 = icmp eq i32 %513, 0
  %515 = zext i1 %514 to i32
  %516 = add i32 %488, %515
  br label %517

517:                                              ; preds = %508, %511
  %518 = phi i32 [ %512, %511 ], [ 0, %508 ]
  %519 = phi i32 [ %516, %511 ], [ %488, %508 ]
  %520 = lshr i32 %518, 7
  %521 = urem i32 %520, %9
  %522 = urem i32 %486, 81
  %523 = lshr i32 %522, 3
  %524 = urem i32 %486, 9
  %525 = icmp eq i32 %522, 0
  %526 = select i1 %525, i32 0, i32 %489
  %527 = mul i32 %500, %16
  %528 = add i32 %527, %523
  %529 = add i32 %528, %519
  %530 = mul i32 %529, %15
  %531 = add nuw nsw i32 %524, 4
  %532 = add nuw nsw i32 %531, %521
  %533 = add i32 %532, %530
  %534 = getelementptr inbounds i32, ptr %19, i32 %533
  %535 = load i32, ptr %534, align 4, !tbaa !10
  %536 = getelementptr inbounds [9 x [9 x i32]], ptr %8, i32 0, i32 %523, i32 %524
  %537 = load i32, ptr %536, align 4, !tbaa !10
  %538 = mul i32 %537, %535
  %539 = add i32 %538, %526
  %540 = icmp eq i32 %522, 80
  br i1 %540, label %541, label %550

541:                                              ; preds = %517
  %542 = lshr i32 %539, 10
  %543 = add i32 %519, -4
  %544 = mul i32 %543, %2
  %545 = lshr i32 %544, 1
  %546 = mul i32 %11, %500
  %547 = add i32 %521, %546
  %548 = add i32 %547, %545
  %549 = getelementptr inbounds i32, ptr %14, i32 %548
  store i32 %542, ptr %549, align 4, !tbaa !10
  br label %550

550:                                              ; preds = %541, %517
  %551 = add nuw nsw i32 %521, 1
  %552 = icmp eq i32 %551, %9
  %553 = add nuw i32 %486, 1
  %554 = select i1 %552, i32 %553, i32 %509
  %555 = select i1 %552, i32 0, i32 %519
  %556 = icmp eq i32 %553, %448
  br i1 %556, label %480, label %485, !llvm.loop !22

557:                                              ; preds = %558, %480
  tail call void @free(ptr noundef %14) #7
  tail call void @free(ptr noundef %19) #7
  call void @llvm.lifetime.end.p0(i64 324, ptr nonnull %8) #7
  call void @llvm.lifetime.end.p0(i64 60, ptr nonnull %7) #7
  ret void

558:                                              ; preds = %481, %558
  %559 = phi i32 [ 0, %481 ], [ %598, %558 ]
  %560 = phi i32 [ 0, %481 ], [ %566, %558 ]
  %561 = urem i32 %559, %9
  %562 = icmp eq i32 %561, 0
  %563 = icmp ne i32 %559, 0
  %564 = and i1 %563, %562
  %565 = zext i1 %564 to i32
  %566 = add i32 %560, %565
  %567 = mul i32 %566, %2
  %568 = lshr i32 %567, 1
  %569 = add nuw i32 %568, %561
  %570 = getelementptr inbounds i32, ptr %14, i32 %569
  %571 = load i32, ptr %570, align 4, !tbaa !10
  %572 = trunc i32 %571 to i16
  %573 = shl i32 %566, 1
  %574 = mul i32 %573, %2
  %575 = shl nuw i32 %561, 1
  %576 = add i32 %574, %575
  %577 = getelementptr inbounds i16, ptr %1, i32 %576
  store i16 %572, ptr %577, align 2, !tbaa !6
  %578 = add i32 %569, %11
  %579 = getelementptr inbounds i32, ptr %14, i32 %578
  %580 = load i32, ptr %579, align 4, !tbaa !10
  %581 = trunc i32 %580 to i16
  %582 = or i32 %576, 1
  %583 = getelementptr inbounds i16, ptr %1, i32 %582
  store i16 %581, ptr %583, align 2, !tbaa !6
  %584 = add i32 %569, %482
  %585 = getelementptr inbounds i32, ptr %14, i32 %584
  %586 = load i32, ptr %585, align 4, !tbaa !10
  %587 = trunc i32 %586 to i16
  %588 = or i32 %573, 1
  %589 = mul i32 %588, %2
  %590 = add i32 %589, %575
  %591 = getelementptr inbounds i16, ptr %1, i32 %590
  store i16 %587, ptr %591, align 2, !tbaa !6
  %592 = add i32 %569, %483
  %593 = getelementptr inbounds i32, ptr %14, i32 %592
  %594 = load i32, ptr %593, align 4, !tbaa !10
  %595 = trunc i32 %594 to i16
  %596 = add i32 %590, 1
  %597 = getelementptr inbounds i16, ptr %1, i32 %596
  store i16 %595, ptr %597, align 2, !tbaa !6
  %598 = add nuw nsw i32 %559, 1
  %599 = icmp eq i32 %598, %484
  br i1 %599, label %557, label %558, !llvm.loop !23
}

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare noalias noundef ptr @malloc(i32 noundef) local_unnamed_addr #2

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare void @free(ptr allocptr nocapture noundef) local_unnamed_addr #3

; Function Attrs: mustprogress nofree nounwind willreturn memory(write)
declare double @exp(double noundef) local_unnamed_addr #4

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.umax.i32(i32, i32) #5

attributes #0 = { mustprogress nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #1 = { nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nofree nounwind willreturn memory(write) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="i686" "target-features"="+cx8,+x87" "tune-cpu"="generic" }
attributes #5 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #6 = { nounwind allocsize(0) }
attributes #7 = { nounwind }

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
!22 = distinct !{!22, !13, !14}
!23 = distinct !{!23, !13, !14}
