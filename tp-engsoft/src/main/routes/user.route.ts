import type { Router } from 'express'

export default class UserRoute {
  private routes: Router
  private controller: any
  constructor(routes: Router, controller: any) {
    this.routes = routes
    this.controller = controller
  }
  public buildRoutes() {
    this.routes.post('/user', this.controller.InsertParticipant)
    this.routes.get('/users', this.controller.getParticipants)
    this.routes.delete('/user', this.controller.deleteParticipants)
  }
}
